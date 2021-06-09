#ifndef UTIL_CONCURRENT_BLOCING_QUEUE_H_
#define UTIL_CONCURRENT_BLOCING_QUEUE_H_

#include <condition_variable>
#include <deque>
#include <mutex>

template <typename T>
struct BlockingQueue {
  BlockingQueue() {}

  ~BlockingQueue() {}

  BlockingQueue(const BlockingQueue&) = delete;
  BlockingQueue& operator=(const BlockingQueue&) = delete;
  BlockingQueue(BlockingQueue&&) = delete;
  BlockingQueue& operator=(BlockingQueue&&) = delete;

  void enqueue(T&& v) {
    {
      std::unique_lock<std::mutex> lk(mutex_);
      queue_.push_back(std::move(v));
    }
    cv_not_empty.notify_all();
  }

  void dequeue(T& v) {
    std::unique_lock<std::mutex> lk(mutex_);
    cv_not_empty.wait(lk, [this] { return !queue_.empty(); });
    v = std::move(queue_.front());
    queue_.pop_front();
  }

 private:
  std::deque<T> queue_;
  std::mutex mutex_;
  std::condition_variable cv_not_empty;
};

#endif  // UTIL_CONCURRENT_BLOCING_QUEUE_H_
