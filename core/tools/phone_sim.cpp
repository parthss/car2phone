// SPDX-License-Identifier: Apache-2.0
// Phone simulator: connects to a car, negotiates streams, pushes a theme and
// navigation / media cards, and prints vehicle signals.
//
//   c2p_phone_sim <host> [theme] [--port P] [--greedy] [--seconds N] [--vanish-after N]
//
// themes: midnight, monsoon, marine, saffron (rejected), lowcontrast (rejected)
// --greedy        also request video on the cluster (the car must deny it)
// --vanish-after  stop sending after N seconds to show the car's 1 s fallback
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>

#include "c2p/session.hpp"
#include "c2p/transport.hpp"
#include "demo_themes.hpp"

using namespace c2p;

namespace {

class Printer : public PhoneSession::Listener {
 public:
  void onStateChanged(SessionState s, const std::string& reason) override {
    std::printf("[phone] state -> %-11s (%s)\n", toString(s), reason.c_str());
  }
  void onCapabilities(const Capabilities& caps) override {
    std::printf("[phone] car: %s, %zu displays\n", caps.vehicleName.c_str(), caps.displays.size());
  }
  void onGrants(const SessionAccept& accept) override {
    for (const auto& g : accept.grants)
      std::printf("[phone]   display %u %-6s %s%s%s\n", g.displayId, modeName(g.mode),
                  g.granted ? "GRANTED" : "DENIED", g.granted ? "" : " — ", g.reason.c_str());
  }
  void onThemeResult(const ThemeResult& r) override {
    std::printf("[phone] theme '%s' %s\n", r.themeId.c_str(), r.accepted ? "accepted" : "REJECTED");
    for (const auto& v : r.violations) std::printf("[phone]   - %s\n", v.c_str());
  }
  void onSignal(const SignalUpdate& s) override { latest[s.path] = s.value; }

  std::map<std::string, double> latest;
};

const char* kRoute[] = {"Western Express Hwy", "Sion Flyover", "Eastern Freeway", "Marine Drive"};
const char* kManeuvers[] = {"straight", "slight-left", "right", "arrive"};

}  // namespace

int main(int argc, char** argv) {
  if (argc < 2) {
    std::fprintf(stderr, "usage: %s <host> [theme] [--port P] [--greedy] [--seconds N] [--vanish-after N]\n", argv[0]);
    return 2;
  }
  std::setvbuf(stdout, nullptr, _IOLBF, 0);
  std::string host = argv[1];
  std::string themeId = "midnight";
  uint16_t port = kDefaultPort;
  bool greedy = false;
  int seconds = 12;
  int vanishAfter = 0;
  for (int i = 2; i < argc; ++i) {
    if (std::strcmp(argv[i], "--port") == 0 && i + 1 < argc) port = static_cast<uint16_t>(std::atoi(argv[++i]));
    else if (std::strcmp(argv[i], "--greedy") == 0) greedy = true;
    else if (std::strcmp(argv[i], "--seconds") == 0 && i + 1 < argc) seconds = std::atoi(argv[++i]);
    else if (std::strcmp(argv[i], "--vanish-after") == 0 && i + 1 < argc) vanishAfter = std::atoi(argv[++i]);
    else themeId = argv[i];
  }

  Theme theme;
  if (!demo::findTheme(themeId, theme)) {
    std::fprintf(stderr, "unknown theme '%s'\n", themeId.c_str());
    return 2;
  }

  std::string err;
  auto conn = tcpConnect(host, port, err);
  if (!conn) {
    std::fprintf(stderr, "error: %s\n", err.c_str());
    return 1;
  }

  PhoneSession session("Car2Phone phone simulator", greedy);
  Printer printer;
  session.setListener(&printer);
  conn->send(session.onConnected(monotonicMs()));

  const uint32_t start = monotonicMs();
  bool pushed = false;
  uint32_t lastCard = 0;
  uint32_t lastPrint = start;
  int step = 0;

  while (conn->isOpen()) {
    std::vector<Frame> frames;
    const bool open = conn->receive(frames, 20);
    const uint32_t now = monotonicMs();
    const bool vanished = vanishAfter > 0 && now - start >= static_cast<uint32_t>(vanishAfter) * 1000u;

    for (const auto& f : frames) {
      auto out = session.onFrame(f, now);
      if (!vanished) conn->send(out);
    }
    if (!open) {
      session.onDisconnected(conn->error());
      break;
    }
    if (session.state() != SessionState::Handshaking && session.state() != SessionState::Active) break;
    if (vanished) {
      if (step >= 0) {
        std::printf("[phone] going silent (simulating the phone leaving the car)\n");
        step = -1;
      }
      continue;
    }
    conn->send(session.tick(now));

    if (session.state() == SessionState::Active) {
      if (!pushed) {
        pushed = true;
        std::printf("[phone] pushing theme '%s'\n", theme.id.c_str());
        conn->send(encode(theme));
        conn->send(encode(MediaCard{"Demo Track", "Demo Artist", 0, 240}));
      }
      if (now - lastCard >= 1000) {
        lastCard = now;
        const int leg = (step / 3) % 4;
        const uint32_t distance = static_cast<uint32_t>(900 - (step % 3) * 300);
        conn->send(encode(NavCard{kManeuvers[leg], distance, kRoute[leg], static_cast<uint32_t>(18 - step % 18)}));
        ++step;
      }
      if (now - lastPrint >= 2000 && !printer.latest.empty()) {
        lastPrint = now;
        std::printf("[phone] signals:");
        for (const auto& [path, value] : printer.latest) std::printf("  %s=%.1f", path.c_str(), value);
        std::printf("\n");
      }
    }
    if (seconds > 0 && now - start >= static_cast<uint32_t>(seconds) * 1000u) {
      conn->send(encode(Bye{"demo finished"}));
      std::printf("[phone] done\n");
      break;
    }
  }
  return 0;
}
