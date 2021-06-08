#ifndef _MPMC_BOUNDED_QUEUE_H_
#define _MPMC_BOUNDED_QUEUE_H_

template <typename T>
struct MPMCBoundedQueue {
  explicit MPMCBoundedQueue(std::uint32_t capacity) {}

  ~MPMCBoundedQueue() {}

  MPMCBoundedQueue(const MPMCBoundedQueue&) = delete;
  MPMCBoundedQueue& operator=(const MPMCBoundedQueue&) = delete;
  MPMCBoundedQueue(MPMCBoundedQueue&&) = delete;
  MPMCBoundedQueue& operator=(MPMCBoundedQueue&&) = delete;
};

#endif  //_MPMC_BOUNDED_QUEUE_H_
