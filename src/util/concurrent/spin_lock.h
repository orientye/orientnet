#ifndef UTIL_CONCURRENT_SPIN_LOCK_H_
#define UTIL_CONCURRENT_SPIN_LOCK_H_

#include <atomic>

// https://rigtorp.se/spinlock/

struct SpinLock {
  std::atomic<bool> lock_= { false };

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

//#if (__GNUC__ > 4 && __GNUC_MINOR > 7) || __has_builtin(__builtin_ia32_pause) //TODO
#if (__GNUC__ > 4 && __GNUC_MINOR > 7)
// clang added this intrinsic in 3.8
// gcc added this intrinsic by 4.7.1
#define YieldProcessor __builtin_ia32_pause
#endif  // __has_builtin(__builtin_ia32_pause)

// If we don't have intrinsics, we can do some inline asm instead.
#ifndef YieldProcessor
#define YieldProcessor() asm volatile("pause")
#endif  // YieldProcessor

#ifdef YieldProcessor
        YieldProcessor();
#endif

#endif  // defined(__i386__) || defined(__x86_64__)

//std::this_thread::yield()?
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

#endif  // UTIL_CONCURRENT_SPIN_LOCK_H_
