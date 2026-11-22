# SPDX-License-Identifier: Apache-2.0
# Portable core: builds on AGL/Yocto, QNX (qcc), the Android NDK and desktop.
cmake_minimum_required(VERSION 3.16)
project(car2phone_core VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(C2P_BUILD_TESTS "Build unit tests" ON)
option(C2P_BUILD_TOOLS "Build the car/phone simulators" ON)

add_library(c2p
  src/frame.cpp
  src/tlv.cpp
  src/messages.cpp
  src/safety.cpp
  src/profile.cpp
  src/session.cpp
  src/transport.cpp
  src/car_host.cpp
  src/c_api.cpp
)
target_include_directories(c2p PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
if(CMAKE_SYSTEM_NAME STREQUAL "QNX")
  target_link_libraries(c2p PUBLIC socket)
endif()
if(NOT MSVC)
  target_compile_options(c2p PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(C2P_BUILD_TOOLS)
  add_executable(c2p_car_sim tools/car_sim.cpp)
  target_link_libraries(c2p_car_sim PRIVATE c2p)
  add_executable(c2p_phone_sim tools/phone_sim.cpp)
  target_link_libraries(c2p_phone_sim PRIVATE c2p)
endif()

if(C2P_BUILD_TESTS)
  enable_testing()
  add_executable(c2p_tests tests/test_main.cpp)
  target_link_libraries(c2p_tests PRIVATE c2p)
  target_compile_definitions(c2p_tests PRIVATE C2P_PROFILE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../profiles")
  add_test(NAME c2p_tests COMMAND c2p_tests)
endif()

install(TARGETS c2p ARCHIVE DESTINATION lib LIBRARY DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
