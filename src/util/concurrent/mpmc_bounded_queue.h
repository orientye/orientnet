#ifndef UTIL_CONCURRENT_MPMC_BOUNDED_QUEUE_H_
#define UTIL_CONCURRENT_MPMC_BOUNDED_QUEUE_H_

template <typename T>
struct MPMCBoundedQueue {
  explicit MPMCBoundedQueue(std::uint32_t capacity) {}

  ~MPMCBoundedQueue() {}

  MPMCBoundedQueue(const MPMCBoundedQueue&) = delete;
  MPMCBoundedQueue& operator=(const MPMCBoundedQueue&) = delete;
  MPMCBoundedQueue(MPMCBoundedQueue&&) = delete;
  MPMCBoundedQueue& operator=(MPMCBoundedQueue&&) = delete;
};

#endif  //UTIL_CONCURRENT_MPMC_BOUNDED_QUEUE_H_
