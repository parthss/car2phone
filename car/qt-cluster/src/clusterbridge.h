// SPDX-License-Identifier: Apache-2.0
// ClusterBridge: the integration seam between the Car2Phone core and a Qt/QML
// cluster HMI. An OEM HMI team binds its own QML to these properties; the QML
// in this repo is only a reference.
//
// Ownership rules (docs/protocol.md §1, §8):
//  - tell-tales and gauge values come from the CAR (here: a local simulator),
//  - the PHONE can only change theme colours/style and the content-zone cards,
//  - on fallback every phone-supplied property reverts to the OEM default.
#pragma once

#include <QColor>
#include <QElapsedTimer>
#include <QObject>
#include <QString>
#include <QTimer>
#include <memory>

#include "c2p/car_host.hpp"

class ClusterBridge : public QObject, private c2p::CarSession::Listener {
  Q_OBJECT
  // Static vehicle info
  Q_PROPERTY(QString vehicleName READ vehicleName CONSTANT)
  Q_PROPERTY(int clusterWidth READ clusterWidth CONSTANT)
  Q_PROPERTY(int clusterHeight READ clusterHeight CONSTANT)
  Q_PROPERTY(int port READ port CONSTANT)
  // Session
  Q_PROPERTY(QString sessionState READ sessionState NOTIFY sessionChanged)
  Q_PROPERTY(QString stateReason READ stateReason NOTIFY sessionChanged)
  // Phone-supplied theme (validated by the core before it gets here)
  Q_PROPERTY(QString themeName READ themeName NOTIFY themeChanged)
  Q_PROPERTY(QColor background READ background NOTIFY themeChanged)
  Q_PROPERTY(QColor foreground READ foreground NOTIFY themeChanged)
  Q_PROPERTY(QColor accent READ accent NOTIFY themeChanged)
  Q_PROPERTY(QString gaugeStyle READ gaugeStyle NOTIFY themeChanged)
  // Car-owned vehicle state
  Q_PROPERTY(double speed READ speed NOTIFY vehicleChanged)
  Q_PROPERTY(double stateOfCharge READ stateOfCharge NOTIFY vehicleChanged)
  Q_PROPERTY(double rangeKm READ rangeKm NOTIFY vehicleChanged)
  Q_PROPERTY(bool seatbeltWarning READ seatbeltWarning NOTIFY vehicleChanged)
  Q_PROPERTY(bool readyIndicator READ readyIndicator NOTIFY vehicleChanged)
  // Phone-supplied content zone
  Q_PROPERTY(bool navVisible READ navVisible NOTIFY navChanged)
  Q_PROPERTY(QString navManeuver READ navManeuver NOTIFY navChanged)
  Q_PROPERTY(QString navRoad READ navRoad NOTIFY navChanged)
  Q_PROPERTY(int navDistanceM READ navDistanceM NOTIFY navChanged)
  Q_PROPERTY(int navEtaMin READ navEtaMin NOTIFY navChanged)
  Q_PROPERTY(bool mediaVisible READ mediaVisible NOTIFY mediaChanged)
  Q_PROPERTY(QString mediaTitle READ mediaTitle NOTIFY mediaChanged)
  Q_PROPERTY(QString mediaArtist READ mediaArtist NOTIFY mediaChanged)

 public:
  ClusterBridge(c2p::VehicleProfile profile, quint16 port, QObject* parent = nullptr);

  bool start(QString* error);

  QString vehicleName() const { return QString::fromStdString(vehicleName_); }
  int clusterWidth() const { return clusterWidth_; }
  int clusterHeight() const { return clusterHeight_; }
  int port() const { return port_; }

  QString sessionState() const { return sessionState_; }
  QString stateReason() const { return stateReason_; }

  QString themeName() const { return QString::fromStdString(theme_.name); }
  QColor background() const { return QColor::fromRgb(theme_.background); }
  QColor foreground() const { return QColor::fromRgb(theme_.foreground); }
  QColor accent() const { return QColor::fromRgb(theme_.accent); }
  QString gaugeStyle() const { return QString::fromStdString(theme_.gaugeStyle); }

  double speed() const { return speed_; }
  double stateOfCharge() const { return soc_; }
  double rangeKm() const { return rangeKm_; }
  bool seatbeltWarning() const { return seatbeltWarning_; }
  bool readyIndicator() const { return true; }

  bool navVisible() const { return navVisible_; }
  QString navManeuver() const { return QString::fromStdString(nav_.maneuver); }
  QString navRoad() const { return QString::fromStdString(nav_.road); }
  int navDistanceM() const { return static_cast<int>(nav_.distanceM); }
  int navEtaMin() const { return static_cast<int>(nav_.etaMin); }
  bool mediaVisible() const { return mediaVisible_; }
  QString mediaTitle() const { return QString::fromStdString(media_.title); }
  QString mediaArtist() const { return QString::fromStdString(media_.artist); }

 signals:
  void sessionChanged();
  void themeChanged();
  void vehicleChanged();
  void navChanged();
  void mediaChanged();

 private:
  // c2p::CarSession::Listener
  void onStateChanged(c2p::SessionState state, const std::string& reason) override;
  void onThemeChanged(const c2p::Theme& theme) override;
  void onNavCard(const c2p::NavCard& card) override;
  void onMediaCard(const c2p::MediaCard& card) override;
  void onCardsCleared() override;

  void pollNetwork();
  void stepVehicle();

  std::unique_ptr<c2p::CarHost> host_;
  std::string vehicleName_;
  int clusterWidth_ = 1920;
  int clusterHeight_ = 720;
  quint16 port_;

  QString sessionState_ = QStringLiteral("idle");
  QString stateReason_;
  c2p::Theme theme_;
  c2p::NavCard nav_;
  c2p::MediaCard media_;
  bool navVisible_ = false;
  bool mediaVisible_ = false;

  // Simulated vehicle. In a real car these come from the OEM's signal service.
  double speed_ = 0.0;
  double soc_ = 82.0;
  double rangeKm_ = 410.0;
  bool seatbeltWarning_ = true;

  QTimer networkTimer_;
  QTimer vehicleTimer_;
  QElapsedTimer clock_;
  qint64 lastPublishMs_ = 0;
};
