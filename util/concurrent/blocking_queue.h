// Copyright (c) 2021 The orientnet Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef UTIL_CONCURRENT_BLOCKING_QUEUE_H_
#define UTIL_CONCURRENT_BLOCKING_QUEUE_H_

#include <condition_variable>
#include <deque>
#include <mutex>
#include <utility>

template <typename T>
struct BlockingQueue {
  BlockingQueue() {}

  ~BlockingQueue() {}

  BlockingQueue(const BlockingQueue&) = delete;
  BlockingQueue& operator=(const BlockingQueue&) = delete;
  BlockingQueue(BlockingQueue&&) = delete;
  BlockingQueue& operator=(BlockingQueue&&) = delete;

  template <class... Args>
  void enqueue(Args&&... args) {
    {
      std::unique_lock<std::mutex> lk(mutex_);
      queue_.emplace_back(std::forward<Args>(args)...);
    }
    cv_not_empty_.notify_all();
  }

  void dequeue(T& v) {
    std::unique_lock<std::mutex> lk(mutex_);
    cv_not_empty_.wait(lk, [this] { return !queue_.empty(); });
    v = std::move(queue_.front());
    queue_.pop_front();
  }

 private:
  std::deque<T> queue_;
  std::mutex mutex_;
  std::condition_variable cv_not_empty_;
};

#endif  // UTIL_CONCURRENT_BLOCKING_QUEUE_H_
