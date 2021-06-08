#ifndef _MPMC_QUEUE_H_
#define _MPMC_QUEUE_H_

template <typename T>
struct MPMCQueue {
  explicit MPMCQueue(std::uint32_t capacity) {
  }

  ~MPMCQueue() {
  }

  MPMCQueue(const MPMCFixedCapacityQueue&) = delete;
  MPMCQueue& operator=(const MPMCFixedCapacityQueue&) = delete;
  MPMCQueue(MPMCFixedCapacityQueue&&) = delete;
  MPMCQueue& operator=(MPMCFixedCapacityQueue&&) = delete;
};

#endif  //_MPMC_QUEUE_H_
