cmake_minimum_required(VERSION 3.10)

# Keep the version below in sync with the one in orientnet.h
project(orientnet VERSION 0.0.1 LANGUAGES C CXX)

include(CMakeDependentOption)

cmake_dependent_option(ORIENTNET_BUILD_TEST
  "Build the unit tests when BUILD_TEST is enabled and we are the root project" ON
  "BUILD_TEST;CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR" OFF)
cmake_dependent_option(ORIENTNET_BUILD_BENCH
  "Build the benchmarks when building unit tests and we are the root project" ON
  "ORIENTNET_BUILD_TEST" OFF)

add_library(orientnet STATIC "")
target_sources(orientnet
  PRIVATE
    "src/util/concurrent/mpmc-fc-queue.h"
    "src/util/concurrent/spsc-fc-queue.h"
    "src/util/log/log.cc"
    "src/util/log/log.h"
)

if(ORIENTNET_BUILD_TEST)
  add_subdirectory(test)
endif()
