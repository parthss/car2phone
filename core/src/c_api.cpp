// SPDX-License-Identifier: Apache-2.0
#include "c2p/c2p.h"

#include <cstring>
#include <new>

#include "c2p/car_host.hpp"

namespace {

void copyError(const std::string& msg, char* err, size_t len) {
  if (err == nullptr || len == 0) return;
  std::strncpy(err, msg.c_str(), len - 1);
  err[len - 1] = '\0';
}

class CallbackListener : public c2p::CarSession::Listener {
 public:
  explicit CallbackListener(const c2p_car_callbacks* cb) {
    if (cb) cb_ = *cb;
  }
  void onStateChanged(c2p::SessionState s, const std::string& reason) override {
    if (cb_.on_state) cb_.on_state(cb_.user, c2p::toString(s), reason.c_str());
  }
  void onThemeChanged(const c2p::Theme& t) override {
    if (cb_.on_theme)
      cb_.on_theme(cb_.user, t.id.c_str(), t.name.c_str(), t.background, t.foreground, t.accent, t.gaugeStyle.c_str());
  }
  void onNavCard(const c2p::NavCard& n) override {
    if (cb_.on_nav_card) cb_.on_nav_card(cb_.user, n.maneuver.c_str(), n.distanceM, n.road.c_str(), n.etaMin);
  }
  void onMediaCard(const c2p::MediaCard& m) override {
    if (cb_.on_media_card) cb_.on_media_card(cb_.user, m.title.c_str(), m.artist.c_str(), m.positionS, m.durationS);
  }
  void onCardsCleared() override {
    if (cb_.on_cards_cleared) cb_.on_cards_cleared(cb_.user);
  }

 private:
  c2p_car_callbacks cb_{};
};

}  // namespace

struct c2p_car {
  c2p_car(c2p::VehicleProfile profile, const c2p_car_callbacks* cb) : host(std::move(profile)), listener(cb) {
    host.session().setListener(&listener);
  }
  c2p::CarHost host;
  CallbackListener listener;
};

extern "C" {

c2p_car* c2p_car_create(const char* profile_path, const c2p_car_callbacks* callbacks, char* err, size_t err_len) {
  c2p::VehicleProfile profile;
  std::string error;
  if (profile_path == nullptr || !c2p::loadProfile(profile_path, profile, error)) {
    copyError(profile_path ? error : "profile path is NULL", err, err_len);
    return nullptr;
  }
  return new (std::nothrow) c2p_car(std::move(profile), callbacks);
}

int c2p_car_listen(c2p_car* car, uint16_t port, char* err, size_t err_len) {
  if (car == nullptr) return -1;
  std::string error;
  if (!car->host.listen(port == 0 ? c2p::kDefaultPort : port, error)) {
    copyError(error, err, err_len);
    return -1;
  }
  return 0;
}

void c2p_car_poll(c2p_car* car, int timeout_ms) {
  if (car) car->host.poll(timeout_ms);
}

void c2p_car_publish_signal(c2p_car* car, const char* vss_path, double value) {
  if (car && vss_path) car->host.publishSignal(vss_path, value);
}

void c2p_car_destroy(c2p_car* car) { delete car; }

}  // extern "C"
