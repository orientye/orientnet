#ifndef _BLOCKGING_BOUNDED_QUEUE_H_
#define _BLOCKGING_BOUNDED_QUEUE_H_

template <typename T>
struct BlockingBoundedQueue {
  explicit BlockingBoundedQueue(std::uint32_t capacity) {}

  ~BlockingBoundedQueue() {}

  BlockingBoundedQueue(const BlockingBoundedQueue&) = delete;
  BlockingBoundedQueue& operator=(const BlockingBoundedQueue&) = delete;
  BlockingBoundedQueue(BlockingBoundedQueue&&) = delete;
  BlockingBoundedQueue& operator=(BlockingBoundedQueue&&) = delete;
};

#endif  //_BLOCKGING_BOUNDED_QUEUE_H_
