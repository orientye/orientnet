#ifndef _SCSP_DYNAMIC_LENGTH_QUEUE_H_
#define _SCSP_DYNAMIC_LENGTH_QUEUE_H_

#include <atomic>
#include <cstdint>
#include <cstdlib>
#include <new>

template <typename T>
struct SCSPDynamicLengthQueue {
  explicit SCSPDynamicLengthQueue(std::uint32_t capacity)
      : capacity_(capacity),
        data_(static_cast<T*>(std::malloc(sizeof(T) * capacity))),
        read_idx_(0),
        write_idx_(0) {
    if (!data_) {
      throw std::bad_alloc();
    }
  }

  ~SCSPDynamicLengthQueue() {
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

  SCSPDynamicLengthQueue(const SCSPDynamicLengthQueue&) = delete;
  SCSPDynamicLengthQueue& operator=(const SCSPDynamicLengthQueue&) = delete;
  SCSPDynamicLengthQueue(const SCSPDynamicLengthQueue&&) = delete;
  SCSPDynamicLengthQueue& operator=(const SCSPDynamicLengthQueue&&) = delete;

  template <class... Args>
  bool write(Args&&... values) {
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

  bool read(T& value) {
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
  T* const data_;
  std::uint32_t capacity_;
  std::atomic<std::uint32_t> read_idx_;
  std::atomic<std::uint32_t> write_idx_;
};

#endif  //_SCSP_DYNAMIC_LENGTH_QUEUE_H_

