// Copyright (c) 2021 The orientnet Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef UTIL_CONCURRENT_SPIN_LOCK_H_
#define UTIL_CONCURRENT_SPIN_LOCK_H_

#include <atomic>

class SpinLock {
  std::atomic_flag lock_ = ATOMIC_FLAG_INIT;

 public:
  void lock() {
    while (lock_.test_and_set(std::memory_order_acquire)) {
      #ifdef __x86_64__
        __builtin_ia32_pause();
      #elif defined(__aarch64__)
        __asm__ __volatile__("yield" ::: "memory");
      #else
        std::this_thread::yield();
      #endif
    }
  }

  bool try_lock() {
    return (lock_.test_and_set(std::memory_order_acquire) == false);
  }

  void unlock() { lock_.clear(std::memory_order_release); }

  SpinLock() = default;
  SpinLock(SpinLock const&) = delete;
  SpinLock& operator=(SpinLock const&) = delete;
  SpinLock(SpinLock&&) = delete;
  SpinLock& operator=(SpinLock&&) = delete;
};

#endif  // UTIL_CONCURRENT_SPIN_LOCK_H_
