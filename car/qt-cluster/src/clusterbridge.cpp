// SPDX-License-Identifier: Apache-2.0
#include "clusterbridge.h"

#include <algorithm>
#include <cmath>

using namespace c2p;

ClusterBridge::ClusterBridge(VehicleProfile profile, quint16 port, QObject* parent)
    : QObject(parent), port_(port) {
  vehicleName_ = profile.capabilities.vehicleName;
  for (const auto& d : profile.capabilities.displays) {
    if (d.role == DisplayRole::Cluster) {
      clusterWidth_ = static_cast<int>(d.width);
      clusterHeight_ = static_cast<int>(d.height);
      break;
    }
  }
  theme_ = profile.defaultTheme;
  host_ = std::make_unique<CarHost>(std::move(profile));
  host_->session().setListener(this);

  networkTimer_.setInterval(16);
  connect(&networkTimer_, &QTimer::timeout, this, &ClusterBridge::pollNetwork);
  vehicleTimer_.setInterval(50);
  connect(&vehicleTimer_, &QTimer::timeout, this, &ClusterBridge::stepVehicle);
}

bool ClusterBridge::start(QString* error) {
  std::string err;
  if (!host_->listen(port_, err)) {
    if (error) *error = QString::fromStdString(err);
    return false;
  }
  clock_.start();
  networkTimer_.start();
  vehicleTimer_.start();
  return true;
}

void ClusterBridge::pollNetwork() { host_->poll(0); }

void ClusterBridge::stepVehicle() {
  const double t = clock_.elapsed() / 1000.0;
  speed_ = std::max(0.0, 45.0 + 35.0 * std::sin(t / 4.0));
  soc_ = std::max(5.0, 82.0 - t / 60.0);
  rangeKm_ = soc_ * 5.0;
  seatbeltWarning_ = t < 6.0 && static_cast<int>(t * 2) % 2 == 0;  // blinks after start
  emit vehicleChanged();

  if (clock_.elapsed() - lastPublishMs_ >= 100) {
    lastPublishMs_ = clock_.elapsed();
    host_->publishSignal("Vehicle.Speed", speed_);
    host_->publishSignal("Vehicle.Powertrain.TractionBattery.StateOfCharge.Displayed", soc_);
    host_->publishSignal("Vehicle.Powertrain.Range", rangeKm_ * 1000.0);
  }
}

void ClusterBridge::onStateChanged(SessionState state, const std::string& reason) {
  sessionState_ = QString::fromLatin1(toString(state));
  stateReason_ = QString::fromStdString(reason);
  emit sessionChanged();
}

void ClusterBridge::onThemeChanged(const Theme& theme) {
  theme_ = theme;
  emit themeChanged();
}

void ClusterBridge::onNavCard(const NavCard& card) {
  nav_ = card;
  navVisible_ = true;
  emit navChanged();
}

void ClusterBridge::onMediaCard(const MediaCard& card) {
  media_ = card;
  mediaVisible_ = true;
  emit mediaChanged();
}

void ClusterBridge::onCardsCleared() {
  navVisible_ = false;
  mediaVisible_ = false;
  emit navChanged();
  emit mediaChanged();
}
