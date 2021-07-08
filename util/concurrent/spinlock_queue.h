// Copyright (c) 2021 The orientnet Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef UTIL_CONCURRENT_SPINLOCK_QUEUE_H_
#define UTIL_CONCURRENT_SPINLOCK_QUEUE_H_

#include <deque>
#include <utility>

#include "util/concurrent/spin_lock.h"

template <typename T>
struct SpinLockQueue {
  SpinLockQueue() {}

  ~SpinLockQueue() {}

  SpinLockQueue(const SpinLockQueue&) = delete;
  SpinLockQueue& operator=(const SpinLockQueue&) = delete;
  SpinLockQueue(SpinLockQueue&&) = delete;
  SpinLockQueue& operator=(SpinLockQueue&&) = delete;

  template <class... Args>
  void enqueue(Args&&... args) {
    spin_lock_.lock();
    queue_.emplace_back(std::forward<Args>(args)...);
    spin_lock_.unlock();
  }

  bool dequeue(T& v) {
    spin_lock_.lock();
    if (queue_.empty()) {
      spin_lock_.unlock();
      return false;
    }
    v = std::move(queue_.front());
    queue_.pop_front();
    spin_lock_.unlock();
    return true;
  }

 private:
  std::deque<T> queue_;
  SpinLock spin_lock_;
};

#endif  // UTIL_CONCURRENT_SPINLOCK_QUEUE_H_
