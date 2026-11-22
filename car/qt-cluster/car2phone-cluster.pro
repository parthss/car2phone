# SPDX-License-Identifier: Apache-2.0
# qmake build (Qt 5.15 / Qt 6). For AGL/Yocto use CMakeLists.txt.
TEMPLATE = app
TARGET = car2phone-cluster
QT += quick
CONFIG += c++17
CONFIG -= app_bundle

CORE = $$PWD/../../core
INCLUDEPATH += $$CORE/include $$PWD/src

HEADERS += src/clusterbridge.h
SOURCES += src/main.cpp src/clusterbridge.cpp $$files($$CORE/src/*.cpp)
RESOURCES += qml.qrc

macx {
    CONFIG += sdk_no_version_check
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 11.0
    # Qt 5.15 still links Apple's long-deprecated AGL (Apple GL) framework,
    # which current macOS SDKs no longer ship. (Unrelated to Automotive Grade Linux.)
    QMAKE_LIBS_OPENGL = -framework OpenGL
}
