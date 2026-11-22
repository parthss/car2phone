# SPDX-License-Identifier: Apache-2.0
# Qt cluster receiver — CMake build for AGL/Yocto (Qt 6) and desktop (Qt 6 or 5.15).
cmake_minimum_required(VERSION 3.16)
project(car2phone_cluster VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Quick)

set(C2P_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(C2P_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../core ${CMAKE_CURRENT_BINARY_DIR}/core)

add_executable(car2phone-cluster
  src/main.cpp
  src/clusterbridge.cpp
  src/clusterbridge.h
  qml.qrc
)
target_link_libraries(car2phone-cluster PRIVATE c2p Qt${QT_VERSION_MAJOR}::Quick)

install(TARGETS car2phone-cluster RUNTIME DESTINATION bin)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../profiles/ DESTINATION share/car2phone/profiles)
