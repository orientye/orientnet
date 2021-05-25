#ifndef _MPMC_FIXED_CAPACITY_QUEUE_H_
#define _MPMC_FIXED_CAPACITY_QUEUE_H_

template <typename T>
struct MPMCFixedCapacityQueue {
  explicit MPMCFixedCapacityQueue(std::uint32_t capacity) {
  }

  ~MPMCFixedCapacityQueue() {
  }

  MPMCFixedCapacityQueue(const MPMCFixedCapacityQueue&) = delete;
  MPMCFixedCapacityQueue& operator=(const MPMCFixedCapacityQueue&) = delete;
  MPMCFixedCapacityQueue(const MPMCFixedCapacityQueue&&) = delete;
  MPMCFixedCapacityQueue& operator=(const MPMCFixedCapacityQueue&&) = delete;
};

#endif  //_MPMC_FIXED_CAPACITY_QUEUE_H_
