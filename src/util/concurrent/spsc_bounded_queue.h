#ifndef UTIL_CONCURRENT_SPSC_BOUNDED_QUEUE_H_
#define UTIL_CONCURRENT_SPSC_BOUNDED_QUEUE_H_

#include <atomic>
#include <cstdint>
#include <cstdlib>
#include <new>

#include "util/align.h"

template <typename T>
struct SPSCBoundedQueue {
  explicit SPSCBoundedQueue(std::uint32_t capacity)
      : capacity_(capacity),
        data_(static_cast<T*>(std::malloc(sizeof(T) * capacity))),
        read_idx_(0),
        write_idx_(0) {
    if (!data_) {
      throw std::bad_alloc();
    }
  }

  ~SPSCBoundedQueue() {
    if (!std::is_trivially_destructible<T>::value) {
      size_t cur_idx = read_idx_;
      size_t end_idx = write_idx_;
      while (cur_idx != end_idx) {
        data_[cur_idx].~T();
        if (++cur_idx == capacity_) {
          cur_idx = 0;
        }
      }
    }
    std::free(data_);
  }

  SPSCBoundedQueue(const SPSCBoundedQueue&) = delete;
  SPSCBoundedQueue& operator=(const SPSCBoundedQueue&) = delete;
  SPSCBoundedQueue(SPSCBoundedQueue&&) = delete;
  SPSCBoundedQueue& operator=(SPSCBoundedQueue&&) = delete;

  template <class... Args>
  bool enqueue(Args&&... values) {
    auto const cur_write = write_idx_.load(std::memory_order_relaxed);
    auto next = cur_write + 1;
    if (next == capacity_) {
      next = 0;
    }
    if (next != read_idx_.load(std::memory_order_acquire)) {
      new (&data_[cur_write]) T(std::forward<Args>(values)...);
      write_idx_.store(next, std::memory_order_release);
      return true;
    }
    // full
    return false;
  }

  bool dequeue(T& value) {
    auto const cur_read = read_idx_.load(std::memory_order_relaxed);
    if (cur_read == write_idx_.load(std::memory_order_acquire)) {
      // empty
      return false;
    }

    auto next = cur_read + 1;
    if (next == capacity_) {
      next = 0;
    }
    value = std::move(data_[cur_read]);
    data_[cur_read].~T();
    read_idx_.store(next, std::memory_order_release);
    return true;
  }

  bool full() {
    auto next = write_idx_.load(std::memory_order_acquire) + 1;
    if (next == capacity_) {
      next = 0;
    }
    if (next != read_idx_.load(std::memory_order_acquire)) {
      return false;
    }
    return true;
  }

  bool empty() {
    return read_idx_.load(std::memory_order_acquire) ==
           write_idx_.load(std::memory_order_acquire);
  }

  std::uint32_t capacity() { return capacity_; }

 private:
  char pad_one_[hardware_destructive_interference_size];
  T* const data_;
  std::uint32_t capacity_;
  alignas(hardware_destructive_interference_size)
      std::atomic<std::uint32_t> read_idx_;
  alignas(hardware_destructive_interference_size)
      std::atomic<std::uint32_t> write_idx_;
  char pad_two_[hardware_destructive_interference_size -
                sizeof(std::atomic<std::uint32_t>)];
};

#endif  //UTIL_CONCURRENT_SPSC_BOUNDED_QUEUE_H_
