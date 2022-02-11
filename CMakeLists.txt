cmake_minimum_required(VERSION 3.16)

set(CMAKE_UNITY_BUILD ON)

# Keep the version below in sync with the one in orientnet.h
project(orientnet VERSION 0.0.1 LANGUAGES C CXX)

include(CMakeDependentOption)
cmake_dependent_option(ORIENTNET_BUILD_TEST
  "Build the unit tests when BUILD_TEST is enabled and we are the root project" ON
  "BUILD_TEST;CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR" OFF)
cmake_dependent_option(ORIENTNET_BUILD_BENCH
  "Build the benchmarks when building unit tests and we are the root project" ON
  "ORIENTNET_BUILD_TEST" OFF)

include(CheckIncludeFiles)
check_include_files("linux/io_uring.h" ORIENTNET_HAVE_LINUX_IO_URING_H)
configure_file("${PROJECT_SOURCE_DIR}/config.h.in" "${PROJECT_SOURCE_DIR}/config.h")

add_library(orientnet STATIC "")

target_compile_features(orientnet PRIVATE cxx_std_17)

target_include_directories(orientnet
  PRIVATE
    "."
    "./3rdparty/protobuf/src"
)

target_sources(orientnet
  PRIVATE
    "net/server.cc"
    "net/server.h"
    "util/concurrent/blocking_bounded_queue.h"
    "util/concurrent/blocking_queue.h"
    "util/concurrent/mpmc_bounded_queue.h"
    "util/concurrent/mpmc_queue.h"
    "util/concurrent/spin_lock.h"
    "util/concurrent/spsc_bounded_queue.h"
    "util/concurrent/spsc_queue.h"
    "util/concurrent/thread_pool.cc"
    "util/concurrent/thread_pool.h"
    "util/log/log_sync.h"
    "util/log/log_sync.cc"
    "util/log/log.cc"
    "util/log/log.h"
)

if(ORIENTNET_BUILD_TEST)
  add_subdirectory(test)
endif()
