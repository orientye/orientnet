#ifndef UTIL_CONCURRENT_MPMC_QUEUE_H_
#define UTIL_CONCURRENT_MPMC_QUEUE_H_

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

#endif  //UTIL_CONCURRENT_MPMC_QUEUE_H_
