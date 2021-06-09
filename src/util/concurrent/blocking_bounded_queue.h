#ifndef UTIL_CONCURRENT_BLOCKGING_BOUNDED_QUEUE_H_
#define UTIL_CONCURRENT_BLOCKGING_BOUNDED_QUEUE_H_

template <typename T>
struct BlockingBoundedQueue {
  explicit BlockingBoundedQueue(std::uint32_t capacity) {}

  ~BlockingBoundedQueue() {}

  BlockingBoundedQueue(const BlockingBoundedQueue&) = delete;
  BlockingBoundedQueue& operator=(const BlockingBoundedQueue&) = delete;
  BlockingBoundedQueue(BlockingBoundedQueue&&) = delete;
  BlockingBoundedQueue& operator=(BlockingBoundedQueue&&) = delete;
};

#endif  //UTIL_CONCURRENT_BLOCKGING_BOUNDED_QUEUE_H_
