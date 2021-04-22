#ifndef _SCSP_DYNAMIC_LENGTH_QUEUE_H_
#define _SCSP_DYNAMIC_LENGTH_QUEUE_H_

#include <atomic>
#include <cstdint>
#include <cstdlib>
#include <new>

template <typename T>
struct SCSPDynamicLengthQueue {
  explicit SCSPDynamicLengthQueue(std::uint32_t capacity)
      : capacity_(capacity),
        data_(static_cast<T*>(std::malloc(sizeof(T) * capacity))),
        read_idx_(0),
        write_idx_(0) {
    if (!data_) {
      throw std::bad_alloc();
    }
  }

  ~SCSPDynamicLengthQueue() {
    if (!std::is_trivially_destructible<T>::value) {
      size_t cur_idx = read_idx_;
      size_t end_idx = write_idx_;
      while (cur_idx != end_idx) {
        data_[cur_idx].~T();
        if (++cur_idx == capacity_) {
          cur_idx = 0;
        }
      }
    }
    std::free(data_);
  }

  SCSPDynamicLengthQueue(const SCSPDynamicLengthQueue&) = delete;
  SCSPDynamicLengthQueue& operator=(const SCSPDynamicLengthQueue&) = delete;
  SCSPDynamicLengthQueue(const SCSPDynamicLengthQueue&&) = delete;
  SCSPDynamicLengthQueue& operator=(const SCSPDynamicLengthQueue&&) = delete;

  template <class... Args>
  bool write(Args&&... values) {
    auto const cur_write = write_idx_.load(std::memory_order_relaxed);
    auto next = cur_write + 1;
    if (next == capacity_) {
      next = 0;
    }
    if (next != read_idx_.load(std::memory_order_acquire)) {
      new (&data_[cur_write]) T(std::forward<Args>(values)...);
      write_idx_.store(next, std::memory_order_release);
      return true;
    }
    // full
    return false;
  }

  bool read(T& value) {
    auto const cur_read = read_idx_.load(std::memory_order_relaxed);
    if (cur_read == write_idx_.load(std::memory_order_acquire)) {
      // empty
      return false;
    }

    auto next = cur_read + 1;
    if (next == capacity_) {
      next = 0;
    }
    value = std::move(data_[cur_read]);
    data_[cur_read].~T();
    read_idx_.store(next, std::memory_order_release);
    return true;
  }

  bool full() {
    auto next = write_idx_.load(std::memory_order_acquire) + 1;
    if (next == capacity_) {
      next = 0;
    }
    if (next != read_idx_.load(std::memory_order_acquire)) {
      return false;
    }
    return true;
  }

  bool empty() {
    return read_idx_.load(std::memory_order_acquire) ==
           write_idx_.load(std::memory_order_acquire);
  }

  std::uint32_t capacity() { return capacity_; }

 private:
  T* const data_;
  std::uint32_t capacity_;
  std::atomic<std::uint32_t> read_idx_;
  std::atomic<std::uint32_t> write_idx_;
};

// load with 'consume' (data-dependent) memory ordering
template <typename T>
T load_consume(T const* addr) {  // hardware fence is implicit on x86
  T v = *const_cast<T const volatile*>(addr);
  __memory_barrier();  // compiler fence
  return v;
}

// store with 'release' memory ordering
template <typename T>
void store_release(T* addr, T v) {  // hardware fence is implicit on x86
  __memory_barrier();               // compiler fence
  *const_cast<T volatile*>(addr) = v;
}

// cache line size on modern x86 processors (in bytes)
size_t const cache_line_size = 64;

// single-producer/single-consumer queue
template <typename T>
class spsc_queue {
 public:
  spsc_queue() {
    node* n = new node;
    n->next_ = 0;
    tail_ = head_ = first_ = tail_copy_ = n;
  }

  ~spsc_queue() {
    node* n = first_;
    do {
      node* next = n->next_;
      delete n;
      n = next;
    } while (n);
  }

  void enqueue(T v) {
    node* n = alloc_node();
    n->next_ = 0;
    n->value_ = v;
    store_release(&head_->next_, n);
    head_ = n;
  }
  // returns 'false' if queue is empty
  bool dequeue(T& v) {
    if (load_consume(&tail_->next_)) {
      v = tail_->next_->value_;
      store_release(&tail_, tail_->next_);
      return true;
    } else {
      return false;
    }
  }

 private:  // internal node structure
  struct node {
    node* next_;
    T value_;
  };
  // consumer partaccessed mainly by consumer, infrequently be producer
  node* tail_;  // tail of the queue
  // delimiter between consumer part and producer part,so that they situated on
  // different cache lines
  char cache_line_pad_[cache_line_size];
  // producer partaccessed only by producer
  node* head_;       // head of the queue
  node* first_;      // last unused node (tail of node cache)
  node* tail_copy_;  // helper (points somewhere between first_ and tail_)

  node* alloc_node() {
    // first tries to allocate node from internal node cache,
    // if attempt fails, allocates node via ::operator new()

    if (first_ != tail_copy_) {
      node* n = first_;
      first_ = first_->next_;
      return n;
    }
    tail_copy_ = load_consume(&tail_);
    if (first_ != tail_copy_) {
      node* n = first_;
      first_ = first_->next_;
      return n;
    }
    node* n = new node;
    return n;
  }

  spsc_queue(spsc_queue const&);
  spsc_queue& operator=(spsc_queue const&);
};

#endif  //_SCSP_DYNAMIC_LENGTH_QUEUE_H_
