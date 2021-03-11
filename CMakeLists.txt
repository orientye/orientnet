cmake_minimum_required(VERSION 3.10)

# Keep the version below in sync with the one in orientnet.h
project(orientnet VERSION 0.0.1 LANGUAGES C CXX)

include(CMakeDependentOption)

cmake_dependent_option(ORIENTNET_BUILD_TESTS
  "Build the unit tests when BUILD_TESTING is enabled and we are the root project" ON
  "BUILD_TEST;CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR" OFF)
cmake_dependent_option(ORIENTNET_BUILD_BENCH
  "Build the benchmarks when building unit tests and we are the root project" ON
  "ORIENTNET_BUILD_TESTS" OFF)

add_library(orientnet STATIC "")
target_sources(orientnet
  PRIVATE
    "src/util/concurrent/scsp-fl-queue.h"
)

if(PRJ_BUILD_TESTS)
  add_subdirectory(test)
endif()
