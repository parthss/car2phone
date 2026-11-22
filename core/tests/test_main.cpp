// SPDX-License-Identifier: Apache-2.0
// Dependency-free unit tests for the Car2Phone core.
#include <cstdio>
#include <cstdlib>
#include <dirent.h>
#include <functional>
#include <string>
#include <vector>

#include "../tools/demo_themes.hpp"
#include "c2p/car_host.hpp"
#include "c2p/frame.hpp"
#include "c2p/messages.hpp"
#include "c2p/profile.hpp"
#include "c2p/safety.hpp"
#include "c2p/session.hpp"
#include "c2p/tlv.hpp"
#include "c2p/transport.hpp"

#ifndef C2P_PROFILE_DIR
#define C2P_PROFILE_DIR "profiles"
#endif

using namespace c2p;

namespace {

int g_failures = 0;
int g_checks = 0;

#define CHECK(cond)                                                         \
  do {                                                                      \
    ++g_checks;                                                             \
    if (!(cond)) {                                                          \
      ++g_failures;                                                         \
      std::fprintf(stderr, "  FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond); \
    }                                                                       \
  } while (0)

struct TestCase {
  const char* name;
  std::function<void()> fn;
};
std::vector<TestCase>& registry() {
  static std::vector<TestCase> r;
  return r;
}
struct Register {
  Register(const char* name, std::function<void()> fn) { registry().push_back({name, std::move(fn)}); }
};
#define TEST(name)                          \
  void name();                              \
  const Register reg_##name(#name, name);   \
  void name()

const char* kTestProfile = R"(
[vehicle]
name = Test car
oem_profile = test
signals = Vehicle.Speed

[display.0]
name = Cluster
role = cluster
width = 1920
height = 720
safety = safety-critical
accepts = theme, cards

[display.1]
name = Center
role = center
width = 1920
height = 720
safety = driver-visible
accepts = video, cards

[display.2]
name = Passenger
role = passenger
width = 1920
height = 720
accepts = video

[theme.default]
id = oem-default
name = Default
background = #000000
foreground = #FFFFFF
accent = #3FA9F5
gauge_style = classic
)";

VehicleProfile testProfile() {
  VehicleProfile p;
  std::string err;
  if (!parseProfile(kTestProfile, p, err)) std::fprintf(stderr, "test profile: %s\n", err.c_str());
  return p;
}

const StreamGrant* findGrant(const SessionAccept& a, uint32_t display, uint32_t mode) {
  for (const auto& g : a.grants)
    if (g.displayId == display && g.mode == mode) return &g;
  return nullptr;
}

// ---------------------------------------------------------------------------
// In-memory car <-> phone link with a fake clock.
struct Link : CarSession::Listener {
  CarSession car;
  PhoneSession phone{"Test phone"};
  uint32_t now = 1000;
  std::vector<Frame> toCar, toPhone;
  std::vector<SignalUpdate> phoneSignals;
  std::vector<ThemeResult> themeResults;
  int navCards = 0;
  int cleared = 0;
  Theme shownTheme;

  struct PhoneListener : PhoneSession::Listener {
    Link* link = nullptr;
    void onSignal(const SignalUpdate& s) override { link->phoneSignals.push_back(s); }
    void onThemeResult(const ThemeResult& r) override { link->themeResults.push_back(r); }
  } phoneListener;

  explicit Link(VehicleProfile p) : car(std::move(p)) {
    car.setListener(this);
    phoneListener.link = this;
    phone.setListener(&phoneListener);
    shownTheme = car.theme();
  }
  void onThemeChanged(const Theme& t) override { shownTheme = t; }
  void onNavCard(const NavCard&) override { ++navCards; }
  void onCardsCleared() override { ++cleared; }

  void phoneSends(std::vector<Frame> frames) { toCar.insert(toCar.end(), frames.begin(), frames.end()); }
  void carSends(std::vector<Frame> frames) { toPhone.insert(toPhone.end(), frames.begin(), frames.end()); }

  // Delivers queued frames (round-tripping through the wire encoding) until quiet.
  void pump() {
    for (int i = 0; i < 20 && (!toCar.empty() || !toPhone.empty()); ++i) {
      auto c = std::move(toCar);
      toCar.clear();
      for (auto& f : c) carSends(car.onFrame(wire(f), now));
      auto p = std::move(toPhone);
      toPhone.clear();
      for (auto& f : p) phoneSends(phone.onFrame(wire(f), now));
    }
  }
  static Frame wire(const Frame& f) {
    FrameDecoder d;
    const auto bytes = encodeFrame(f);
    d.feed(bytes.data(), bytes.size());
    Frame out;
    d.next(out);
    return out;
  }
  void connect() {
    car.onConnected(now);
    phoneSends(phone.onConnected(now));
    pump();
  }
  void advance(uint32_t ms, bool phoneAlive = true) {
    for (uint32_t t = 0; t < ms; t += 50) {
      now += 50;
      carSends(car.tick(now));
      if (phoneAlive) phoneSends(phone.tick(now));
      if (!phoneAlive) toCar.clear();  // phone vanished: its frames never arrive
      pump();
    }
  }
};

}  // namespace

// ===========================================================================
TEST(frame_roundtrip_and_partial_reads) {
  Frame f;
  f.channel = 3;
  f.type = 0xBEEF;
  f.payload = {1, 2, 3, 4, 5};
  const auto bytes = encodeFrame(f);
  CHECK(bytes.size() == kHeaderSize + 5);

  FrameDecoder d;
  Frame out;
  d.feed(bytes.data(), 7);
  CHECK(d.next(out) == FrameDecoder::Status::NeedMore);
  d.feed(bytes.data() + 7, bytes.size() - 7);
  d.feed(bytes.data(), bytes.size());  // a second frame back-to-back
  CHECK(d.next(out) == FrameDecoder::Status::Ok);
  CHECK(out.channel == 3 && out.type == 0xBEEF && out.payload == f.payload);
  CHECK(d.next(out) == FrameDecoder::Status::Ok);
  CHECK(d.next(out) == FrameDecoder::Status::NeedMore);
}

TEST(frame_rejects_bad_magic_and_version) {
  auto bytes = encodeFrame(Frame{});
  bytes[0] = 'X';
  FrameDecoder d;
  Frame out;
  d.feed(bytes.data(), bytes.size());
  CHECK(d.next(out) == FrameDecoder::Status::Error);

  auto v = encodeFrame(Frame{});
  v[2] = 9;
  FrameDecoder d2;
  d2.feed(v.data(), v.size());
  CHECK(d2.next(out) == FrameDecoder::Status::Error);
}

TEST(tlv_roundtrip_and_truncation) {
  TlvWriter inner;
  inner.u32(1, 42);
  TlvWriter w;
  w.u32(1, 0xDEADBEEF).f64(2, -12.5).str(3, "Marine Drive").nested(4, inner).str(5, "");
  TlvReader r(w.data());
  TlvField f;
  CHECK(r.next(f) && f.tag == 1 && f.asU32() == 0xDEADBEEF);
  CHECK(r.next(f) && f.tag == 2 && f.asF64() == -12.5);
  CHECK(r.next(f) && f.tag == 3 && f.asStr() == "Marine Drive");
  CHECK(r.next(f) && f.tag == 4);
  TlvReader nested(f);
  TlvField nf;
  CHECK(nested.next(nf) && nf.asU32() == 42);
  CHECK(r.next(f) && f.tag == 5 && f.asStr().empty());
  CHECK(!r.next(f) && r.ok());

  auto bytes = w.data();
  bytes.pop_back();
  TlvReader bad(bytes);
  while (bad.next(f)) {
  }
  CHECK(!bad.ok());
}

TEST(messages_roundtrip) {
  const VehicleProfile p = testProfile();
  Capabilities caps;
  CHECK(decode(encode(p.capabilities), caps));
  CHECK(caps.vehicleName == "Test car" && caps.displays.size() == 3 && caps.vssSignals.size() == 1);
  CHECK(caps.displays[0].role == DisplayRole::Cluster && caps.displays[0].safety == SafetyClass::SafetyCritical);
  CHECK(caps.displays[1].accepts == (kModeVideo | kModeCards));

  Theme t{"midnight", "Midnight", 0x0B1020, 0xE8ECF4, 0x4FC3F7, "minimal"};
  Theme t2;
  CHECK(decode(encode(t), t2));
  CHECK(t2.id == t.id && t2.accent == t.accent && t2.gaugeStyle == "minimal");

  SessionAccept a;
  a.grants.push_back({0, kModeVideo, false, "nope"});
  SessionAccept a2;
  CHECK(decode(encode(a), a2));
  CHECK(a2.grants.size() == 1 && !a2.grants[0].granted && a2.grants[0].reason == "nope");

  Hello h;
  CHECK(!decode(encode(t), h));  // wrong message type is rejected
}

TEST(policy_never_streams_video_to_cluster) {
  const auto displays = testProfile().capabilities.displays;
  CHECK(!evaluateRequest({0, kModeVideo}, displays).granted);  // cluster
  CHECK(evaluateRequest({0, kModeTheme}, displays).granted);
  CHECK(evaluateRequest({1, kModeVideo}, displays).granted);   // center
  CHECK(!evaluateRequest({1, kModeTheme}, displays).granted);  // center does not accept theme
  CHECK(evaluateRequest({2, kModeVideo}, displays).granted);   // passenger
  CHECK(!evaluateRequest({9, kModeVideo}, displays).granted);  // unknown
  CHECK(!evaluateRequest({0, kModeTheme | kModeCards}, displays).granted);  // one mode per request

  // Even if an OEM profile lists video on the cluster by mistake, it is denied.
  auto risky = displays;
  risky[0].accepts |= kModeVideo;
  CHECK(!evaluateRequest({0, kModeVideo}, risky).granted);
}

TEST(theme_validation) {
  for (const char* id : {"midnight", "monsoon", "marine"}) {
    Theme t;
    CHECK(demo::findTheme(id, t));
    CHECK(validateTheme(t).empty());
  }
  Theme saffron, low;
  demo::findTheme("saffron", saffron);
  demo::findTheme("lowcontrast", low);
  const auto sv = validateTheme(saffron);
  CHECK(sv.size() == 1 && sv[0].find("amber") != std::string::npos);
  CHECK(!validateTheme(low).empty());

  CHECK(reservedTellTaleColour(0xFF0000) == "red");
  CHECK(reservedTellTaleColour(0xFFB000) == "amber");
  CHECK(reservedTellTaleColour(0x3FA9F5).empty());
  CHECK(reservedTellTaleColour(0x5A2020).empty());  // dark, desaturated red is fine
  CHECK(contrastRatio(0x000000, 0xFFFFFF) > 20.9);

  Theme odd{"x", "x", 0x000000, 0xFFFFFF, 0x3FA9F5, "rainbow"};
  CHECK(validateTheme(odd).size() == 1);
}

TEST(all_shipped_profiles_load_and_defaults_are_valid) {
  DIR* dir = opendir(C2P_PROFILE_DIR);
  CHECK(dir != nullptr);
  if (!dir) return;
  int count = 0;
  while (dirent* e = readdir(dir)) {
    const std::string name = e->d_name;
    if (name.size() < 4 || name.substr(name.size() - 4) != ".ini") continue;
    VehicleProfile p;
    std::string err;
    const bool ok = loadProfile(std::string(C2P_PROFILE_DIR) + "/" + name, p, err);
    if (!ok) std::fprintf(stderr, "  %s\n", err.c_str());
    CHECK(ok);
    CHECK(validateTheme(p.defaultTheme).empty());
    bool hasCluster = false;
    for (const auto& d : p.capabilities.displays) {
      if (d.role == DisplayRole::Cluster) {
        hasCluster = true;
        CHECK(!(d.accepts & kModeVideo));
        CHECK(d.safety == SafetyClass::SafetyCritical);
      }
    }
    CHECK(hasCluster);
    ++count;
  }
  closedir(dir);
  CHECK(count >= 5);
}

TEST(profile_parse_errors_are_reported) {
  VehicleProfile p;
  std::string err;
  CHECK(!parseProfile("[display.0]\nrole = spaceship\n", p, err));
  CHECK(err.find("line 2") != std::string::npos);
  CHECK(!parseProfile("[vehicle]\nname = x\n", p, err));  // no displays
}

TEST(session_end_to_end) {
  Link link(testProfile());
  link.connect();
  CHECK(link.car.state() == SessionState::Active);
  CHECK(link.phone.state() == SessionState::Active);
  CHECK(link.phone.capabilities().displays.size() == 3);

  // Phone asked for theme+cards on the cluster, video on center and passenger.
  CHECK(link.phone.granted(0, kModeTheme));
  CHECK(link.phone.granted(0, kModeCards));
  CHECK(!link.phone.granted(0, kModeVideo));
  CHECK(link.phone.granted(1, kModeVideo));
  CHECK(link.phone.granted(2, kModeVideo));

  // Valid theme applies; invalid theme is refused and the shown theme stays.
  Theme midnight, saffron;
  demo::findTheme("midnight", midnight);
  demo::findTheme("saffron", saffron);
  link.phoneSends({encode(midnight)});
  link.pump();
  CHECK(link.shownTheme.id == "midnight");
  link.phoneSends({encode(saffron)});
  link.pump();
  CHECK(link.shownTheme.id == "midnight");
  CHECK(link.themeResults.size() == 2 && link.themeResults[0].accepted && !link.themeResults[1].accepted);

  link.phoneSends({encode(NavCard{"left", 300, "MG Road", 12})});
  link.pump();
  CHECK(link.navCards == 1);

  // Vehicle data: advertised signals flow, others do not.
  link.carSends(link.car.publishSignal("Vehicle.Speed", 42.0));
  link.carSends(link.car.publishSignal("Vehicle.Cabin.Door.Row1.Left.IsOpen", 1.0));
  link.pump();
  CHECK(link.phoneSignals.size() == 1 && link.phoneSignals[0].value == 42.0);

  // Heartbeats keep the session alive.
  link.advance(3000);
  CHECK(link.car.state() == SessionState::Active);

  // Phone vanishes: within ~1 s the car falls back to its own default theme.
  link.advance(1200, /*phoneAlive=*/false);
  CHECK(link.car.state() == SessionState::Fallback);
  CHECK(link.shownTheme.id == "oem-default");
  CHECK(link.cleared >= 1);
}

TEST(session_bye_and_reconnect) {
  Link link(testProfile());
  link.connect();
  link.phoneSends({encode(Bye{"user disconnected"})});
  link.pump();
  CHECK(link.car.state() == SessionState::Idle);
  link.connect();
  CHECK(link.car.state() == SessionState::Active);
}

TEST(theme_without_grant_is_refused) {
  VehicleProfile p = testProfile();
  p.capabilities.displays[0].accepts = kModeCards;  // no display accepts themes
  Link link(std::move(p));
  link.connect();
  Theme t;
  demo::findTheme("midnight", t);
  link.phoneSends({encode(t)});
  link.pump();
  CHECK(link.themeResults.size() == 1 && !link.themeResults[0].accepted);
  CHECK(link.shownTheme.id == "oem-default");
}

TEST(greedy_phone_is_denied_cluster_video) {
  VehicleProfile p = testProfile();
  p.capabilities.displays[0].accepts |= kModeVideo;  // misconfigured profile
  const SessionStart greedy = PhoneSession::defaultRequests(p.capabilities, /*greedy=*/true);
  CarSession car(p);
  car.onConnected(0);
  car.onFrame(encode(Hello{kProtocolVersion, "phone", "greedy"}), 0);
  const auto out = car.onFrame(encode(greedy), 0);
  SessionAccept accept;
  CHECK(out.size() == 1 && decode(out[0], accept));
  const StreamGrant* g = findGrant(accept, 0, kModeVideo);
  CHECK(g != nullptr && !g->granted && !g->reason.empty());
}

TEST(tcp_loopback_handshake) {
  const uint16_t port = 47421;
  CarHost host(testProfile());
  std::string err;
  CHECK(host.listen(port, err));
  auto conn = tcpConnect("127.0.0.1", port, err);
  CHECK(conn != nullptr);
  if (!conn) return;
  PhoneSession phone("loopback phone");
  conn->send(phone.onConnected(monotonicMs()));
  for (int i = 0; i < 40 && phone.state() != SessionState::Active; ++i) {
    host.poll(5);
    std::vector<Frame> frames;
    conn->receive(frames, 5);
    for (const auto& f : frames) conn->send(phone.onFrame(f, monotonicMs()));
  }
  CHECK(phone.state() == SessionState::Active);
  CHECK(host.session().state() == SessionState::Active);
}

int main() {
  for (const auto& t : registry()) {
    const int before = g_failures;
    t.fn();
    std::printf("%s %s\n", g_failures == before ? "ok  " : "FAIL", t.name);
  }
  std::printf("\n%d checks, %d failures\n", g_checks, g_failures);
  return g_failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
