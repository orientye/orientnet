#ifndef _BLOCING_QUEUE_H_
#define _BLOCING_QUEUE_H_

#include <condition_variable>
#include <deque>
#include <mutex>

template <typename T>
struct BlockingQueue {
  BlockingQueue() {}

  ~BlockingQueue() {}

  void enqueue(T&& v) {
    {
      std::unique_lock<std::mutex> lk(mutex_);
      queue_.push_back(std::move(x));
    }
    cv_not_empty.notify_all();
  }

  T dequeue() {
    std::unique_lock<std::mutex> lk(mutex_);
    cv_not_empty.wait(lk, [] { return !queue_.empty() });
    assert(!queue_.empty());
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
  std::mutex mutex_;
  std::condition_variable cv_not_empty;
};

#endif  //_BLOCING_QUEUE_H_
