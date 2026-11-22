// SPDX-License-Identifier: Apache-2.0
// car2phone-cluster <profile.ini> [--port N] [--screenshot out.png --after MS]
//
// --screenshot grabs the cluster's own window after MS milliseconds and exits.
// Used for automated visual checks (works with QT_QPA_PLATFORM=offscreen).
#include <QGuiApplication>
#include <QImage>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QStringList>
#include <QTimer>
#include <cstdio>

#include "clusterbridge.h"

int main(int argc, char* argv[]) {
  QGuiApplication app(argc, argv);
  app.setApplicationName(QStringLiteral("car2phone-cluster"));

  const QStringList args = app.arguments();
  QString profilePath;
  quint16 port = c2p::kDefaultPort;
  QString screenshotPath;
  int screenshotAfterMs = 2000;
  for (int i = 1; i < args.size(); ++i) {
    if (args[i] == QLatin1String("--port") && i + 1 < args.size()) port = static_cast<quint16>(args[++i].toUInt());
    else if (args[i] == QLatin1String("--screenshot") && i + 1 < args.size()) screenshotPath = args[++i];
    else if (args[i] == QLatin1String("--after") && i + 1 < args.size()) screenshotAfterMs = args[++i].toInt();
    else profilePath = args[i];
  }
  if (profilePath.isEmpty()) {
    std::fprintf(stderr, "usage: car2phone-cluster <profile.ini> [--port N]\n");
    return 2;
  }

  c2p::VehicleProfile profile;
  std::string err;
  if (!c2p::loadProfile(profilePath.toStdString(), profile, err)) {
    std::fprintf(stderr, "error: %s\n", err.c_str());
    return 1;
  }

  ClusterBridge bridge(std::move(profile), port);
  QString error;
  if (!bridge.start(&error)) {
    std::fprintf(stderr, "error: %s\n", qPrintable(error));
    return 1;
  }

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty(QStringLiteral("bridge"), &bridge);
  engine.load(QUrl(QStringLiteral("qrc:/qml/Cluster.qml")));
  if (engine.rootObjects().isEmpty()) return 1;

  if (!screenshotPath.isEmpty()) {
    auto* window = qobject_cast<QQuickWindow*>(engine.rootObjects().first());
    QTimer::singleShot(screenshotAfterMs, &app, [window, screenshotPath]() {
      const QImage image = window ? window->grabWindow() : QImage();
      if (image.isNull()) std::fprintf(stderr, "grabWindow returned an empty image\n");
      const bool ok = !image.isNull() && image.save(screenshotPath);
      std::fprintf(ok ? stdout : stderr, "%s %s\n", ok ? "saved" : "failed to save", qPrintable(screenshotPath));
      QCoreApplication::exit(ok ? 0 : 1);
    });
  }
  return app.exec();
}
