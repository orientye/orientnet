#ifndef _BLOCING_QUEUE_H_
#define _BLOCING_QUEUE_H_

#include <deque>

template <typename T>
struct BlockingQueue {
  BlockingQueue() {}

  ~BlockingQueue() {}

  void enqueue(T&& v) {}

  T dequeue() {
    T front(std::move(queue_.front()));
    queue_.pop_front();
    return front;
  }

  BlockingQueue(const BlockingQueue&) = delete;
  BlockingQueue& operator=(const BlockingQueue&) = delete;
  BlockingQueue(BlockingQueue&&) = delete;
  BlockingQueue& operator=(BlockingQueue&&) = delete;

 private:
  std::deque<T> queue_;
};

#endif  //_BLOCING_QUEUE_H_
