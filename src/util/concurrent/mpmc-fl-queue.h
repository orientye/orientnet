#ifndef _MPMC_FIXED_LENGTH_QUEUE_H_
#define _MPMC_FIXED_LENGTH_QUEUE_H_

template <typename T>
struct MPMCFixedLengthQueue {
  explicit MPMCFixedLengthQueue(std::uint32_t capacity) {
  }

  ~MPMCFixedLengthQueue() {
  }

  MPMCFixedLengthQueue(const MPMCFixedLengthQueue&) = delete;
  MPMCFixedLengthQueue& operator=(const MPMCFixedLengthQueue&) = delete;
  MPMCFixedLengthQueue(const MPMCFixedLengthQueue&&) = delete;
  MPMCFixedLengthQueue& operator=(const MPMCFixedLengthQueue&&) = delete;
};

#endif  //_MPMC_FIXED_LENGTH_QUEUE_H_
