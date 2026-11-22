# SPDX-License-Identifier: Apache-2.0
cmake_minimum_required(VERSION 3.22)
project(c2p_jni LANGUAGES CXX)

set(C2P_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(C2P_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../core ${CMAKE_CURRENT_BINARY_DIR}/core)

add_library(c2p_jni SHARED jni_bridge.cpp)
target_link_libraries(c2p_jni PRIVATE c2p log)
