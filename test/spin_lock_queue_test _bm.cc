// Copyright (c) 2021 The orientnet Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include <string>
#include <thread>
#include <vector>

#include "test/3rdparty/doctest/doctest.h"
#include "test/benchmark.h"
#include "util/concurrent/spinlock_queue.h"

namespace SLQTB {

////////////////////////////////////////////////////////////////////////////////////
// https://rigtorp.se/spinlock/

struct SpinLockPause {
  std::atomic<bool> lock_ = {false};

  void lock() noexcept {
    for (;;) {
      // Optimistically assume the lock is free on the first try
      if (!lock_.exchange(true, std::memory_order_acquire)) {
        return;
      }
      // Wait for lock to be released without generating cache misses
      while (lock_.load(std::memory_order_relaxed)) {
// Issue X86 PAUSE or ARM YIELD instruction to reduce contention between
// hyper-threads

// https://github.com/dotnet/coreclr/blob/0fbd855e38bc3ec269479b5f6bf561dcfd67cbb6/src/gc/env/gcenv.base.h
#if defined(__i386__) || defined(__x86_64__)

#define YieldProcessor __builtin_ia32_pause

// If we don't have intrinsics, we can do some inline asm instead.
#ifndef YieldProcessor
#define YieldProcessor() asm volatile("pause")
#endif  // YieldProcessor

#ifdef YieldProcessor
        YieldProcessor();
#endif

#endif  // defined(__i386__) || defined(__x86_64__)

        // std::this_thread::yield();?
      }
    }
  }

  bool try_lock() noexcept {
    // First do a relaxed load to check if lock is free in order to prevent
    // unnecessary cache misses if someone does while(!try_lock())
    return !lock_.load(std::memory_order_relaxed) &&
           !lock_.exchange(true, std::memory_order_acquire);
  }

  void unlock() noexcept { lock_.store(false, std::memory_order_release); }
};

////////////////////////////////////////////////////////////////////////////////////
#ifdef __GNUC__
struct SpinLockGCC {
  volatile int lock_ = 0;

  void lock() {
    while (__sync_lock_test_and_set(&lock_, 1)) {
    }
  }

  bool try_lock() { return __sync_lock_test_and_set(&lock_, 1) == 0; }

  void unlock() { __sync_lock_release(&lock_); }
};
#endif
////////////////////////////////////////////////////////////////////////////////////

struct SpinLocBoolAtomic {
  std::atomic<bool> lock_ = {false};

  void lock() {
    while (lock_.exchange(true, std::memory_order_acquire)) {
    }
  }

  void unlock() { lock_.store(false, std::memory_order_release); }
};

//////////////////////////////////////////////////////////////////////////////////////

// NOTE: performance my benchmark SPSC: __sync_lock_test_and_set >
// std::atomic_flag > std::atomic<bool> > https://rigtorp.se/spinlock/

}  // namespace SLQTB

//////////////////////////////////////////////////////////////////////
TEST_CASE("SpinLockQueue correct") {
    Benchmark bm;
    bm.count("SpinLockQueue correct");
}

TEST_CASE("SpinLockQueue perf") {}

TEST_CASE("SpinLockQueue destructor") {}

TEST_CASE("SpinLockQueue empty and full") {}
