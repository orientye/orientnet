// Copyright (c) 2021 The orientnet Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef TEST_BENCHMARK_H_
#define TEST_BENCHMARK_H_

#include <chrono>

struct Benchmark {
  Benchmark() : start_(std::chrono::steady_clock::now()) {}

  void count(const char* desc) {
    auto duration = std::chrono::steady_clock::now() - start_;
    auto nano_seconds =
        std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    auto milli_seconds =
        std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    auto sceconds = std::chrono::duration<double>(duration).count();
    printf("%s: %llu(nano seconds), %llu(milli seconds), %f(seconds)\n", desc,
           nano_seconds, milli_seconds, sceconds);
    reset();
  }

  void reset() { start_ = std::chrono::steady_clock::now(); }

 private:
  std::chrono::time_point<std::chrono::steady_clock> start_;
};

#endif  // TEST_BENCHMARK_H_
