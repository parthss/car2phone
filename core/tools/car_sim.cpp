// SPDX-License-Identifier: Apache-2.0
// Headless car: loads a vehicle profile, waits for a phone, prints what the
// cluster would show, and publishes simulated speed / battery signals.
//
//   c2p_car_sim <profile.ini> [port] [--seconds N]
#include <cmath>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "c2p/car_host.hpp"

using namespace c2p;

namespace {

volatile std::sig_atomic_t g_stop = 0;
void onSignal(int) { g_stop = 1; }

class Printer : public CarSession::Listener {
 public:
  void onStateChanged(SessionState s, const std::string& reason) override {
    std::printf("[car] state -> %-11s (%s)\n", toString(s), reason.c_str());
  }
  void onThemeChanged(const Theme& t) override {
    std::printf("[car] cluster theme: %s (%s) bg #%06X fg #%06X accent #%06X, %s gauges\n", t.name.c_str(),
                t.id.c_str(), t.background, t.foreground, t.accent, t.gaugeStyle.c_str());
  }
  void onNavCard(const NavCard& n) override {
    std::printf("[car] cluster nav card: %s in %u m onto %s (ETA %u min)\n", n.maneuver.c_str(), n.distanceM,
                n.road.c_str(), n.etaMin);
  }
  void onMediaCard(const MediaCard& m) override {
    std::printf("[car] cluster media card: %s - %s\n", m.title.c_str(), m.artist.c_str());
  }
  void onCardsCleared() override { std::printf("[car] cluster cards cleared\n"); }
};

}  // namespace

int main(int argc, char** argv) {
  if (argc < 2) {
    std::fprintf(stderr, "usage: %s <profile.ini> [port] [--seconds N]\n", argv[0]);
    return 2;
  }
  std::setvbuf(stdout, nullptr, _IOLBF, 0);
  uint16_t port = kDefaultPort;
  int seconds = 0;
  for (int i = 2; i < argc; ++i) {
    if (std::strcmp(argv[i], "--seconds") == 0 && i + 1 < argc) seconds = std::atoi(argv[++i]);
    else port = static_cast<uint16_t>(std::atoi(argv[i]));
  }

  VehicleProfile profile;
  std::string err;
  if (!loadProfile(argv[1], profile, err)) {
    std::fprintf(stderr, "error: %s\n", err.c_str());
    return 1;
  }

  std::printf("[car] %s (%s)\n", profile.capabilities.vehicleName.c_str(), profile.capabilities.oemProfile.c_str());
  for (const auto& d : profile.capabilities.displays)
    std::printf("[car]   display %u: %-26s %-9s %ux%u\n", d.id, d.name.c_str(), toString(d.role), d.width, d.height);

  CarHost host(profile);
  Printer printer;
  host.session().setListener(&printer);
  if (!host.listen(port, err)) {
    std::fprintf(stderr, "error: %s\n", err.c_str());
    return 1;
  }
  std::printf("[car] listening on port %u — run c2p_phone_sim to connect\n", port);

  std::signal(SIGINT, onSignal);
  std::signal(SIGTERM, onSignal);
  const uint32_t start = monotonicMs();
  uint32_t lastSignal = start;
  while (!g_stop) {
    host.poll(20);
    const uint32_t now = monotonicMs();
    if (now - lastSignal >= 100) {
      lastSignal = now;
      const double t = (now - start) / 1000.0;
      host.publishSignal("Vehicle.Speed", 45.0 + 35.0 * std::sin(t / 4.0));
      host.publishSignal("Vehicle.Powertrain.TractionBattery.StateOfCharge.Displayed", 82.0 - t / 60.0);
      host.publishSignal("Vehicle.Powertrain.FuelSystem.Level", 64.0 - t / 120.0);
      host.publishSignal("Vehicle.Powertrain.Range", 410000.0 - t * 12.0);
    }
    if (seconds > 0 && now - start >= static_cast<uint32_t>(seconds) * 1000u) break;
  }
  std::printf("[car] shutting down\n");
  return 0;
}
