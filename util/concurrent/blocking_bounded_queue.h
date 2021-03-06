// Copyright (c) 2021 The orientnet Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef UTIL_CONCURRENT_BLOCKING_BOUNDED_QUEUE_H_
#define UTIL_CONCURRENT_BLOCKING_BOUNDED_QUEUE_H_

#include <condition_variable>
#include <cstdint>
#include <mutex>
#include <new>
#include <utility>

template <typename T>
struct BlockingBoundedQueue {
  explicit BlockingBoundedQueue(std::uint32_t capacity)
      : capacity_(capacity),
        data_(static_cast<T*>(std::malloc(sizeof(T) * capacity))),
        read_idx_(0),
        write_idx_(0) {
    if (!data_) {
      throw std::bad_alloc();
    }
  }

  ~BlockingBoundedQueue() {
    if (!std::is_trivially_destructible<T>::value) {
      auto cur_idx = read_idx_;
      auto end_idx = write_idx_;
      while (cur_idx != end_idx) {
        data_[cur_idx].~T();
        if (++cur_idx == capacity_) {
          cur_idx = 0;
        }
      }
    }
    std::free(data_);
  }

  BlockingBoundedQueue(const BlockingBoundedQueue&) = delete;
  BlockingBoundedQueue& operator=(const BlockingBoundedQueue&) = delete;
  BlockingBoundedQueue(BlockingBoundedQueue&&) = delete;
  BlockingBoundedQueue& operator=(BlockingBoundedQueue&&) = delete;

  template <class... Args>
  void enqueue(Args&&... args) {
    std::unique_lock<std::mutex> lk(mutex_);
    cv_not_full.wait(lk, [this] {
      auto const cur_write = write_idx_;
      auto next = cur_write + 1;
      if (next == capacity_) {
        next = 0;
      }
      return (next != read_idx_);
    });
    auto const cur_write = write_idx_;
    auto next = cur_write + 1;
    if (next == capacity_) {
      next = 0;
    }
    new (&data_[cur_write]) T(std::forward<Args>(args)...);
    write_idx_ = next;
    cv_not_empty.notify_all();
  }

  void dequeue(T& v) {
    std::unique_lock<std::mutex> lk(mutex_);
    cv_not_empty.wait(lk, [this] { return (read_idx_ != write_idx_); });
    auto const cur_read = read_idx_;
    auto next = cur_read + 1;
    if (next == capacity_) {
      next = 0;
    }
    v = std::move(data_[cur_read]);
    data_[cur_read].~T();
    read_idx_ = next;
    cv_not_full.notify_all();
  }

 private:
  T* const data_;
  std::uint32_t capacity_;
  std::mutex mutex_;
  std::uint32_t read_idx_;
  std::uint32_t write_idx_;
  std::condition_variable cv_not_empty;
  std::condition_variable cv_not_full;
};

#endif  // UTIL_CONCURRENT_BLOCKING_BOUNDED_QUEUE_H_
