#ifndef UTIL_CONCURRENT_SPIN_LOCK_H_
#define UTIL_CONCURRENT_SPIN_LOCK_H_

#include <atomic>

class SpinLock {
  std::atomic_flag lock_ = ATOMIC_FLAG_INIT;

 public:
  void lock() {
    while (lock_.test_and_set(std::memory_order_acquire))
      ;
  }

  bool try_lock() {
    return (lock_.test_and_set(std::memory_order_acquire) == false);
  }

  void unlock() { lock_.clear(std::memory_order_release); }
};

#endif  // UTIL_CONCURRENT_SPIN_LOCK_H_
