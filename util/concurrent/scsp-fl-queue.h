#ifdef _SCSP_FIXED_LENGTH_QUEUE_H_

#include <atomic>

template<typename T>
struct SCSPFixedLengthQueue {
    SCSPFixedLengthQueue(std::uint32_t capacity) {
    
    }
    
    ~SCSPFixedLengthQueue() {
    
    }
    
    SCSPFixedLengthQueue(const SCSPFixedLengthQueue&) = delete;
    SCSPFixedLengthQueue& operator=(const SCSPFixedLengthQueue&) = delete;
    SCSPFixedLengthQueue(const SCSPFixedLengthQueue&&) = delete;
    SCSPFixedLengthQueue& operator=(const SCSPFixedLengthQueue&&) = delete;
    
    void push(const T& value) {
    
    }

    void push(T&& value) {
    
    }

    T* front() {
    
    }

    void pop() {

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
        return read_idx_.load(std::memory_order_acquire) == write_idx_.load(std::memory_order_acquire);
    }
    
    void clear() {
    
    }
    
    std::uint32_t capacity() {
    	return capacity_;
    }
private:
    T* data_;
    std::uint32_t capacity_;
    std::atomic<std::uint32_t> read_idx_;
    std::atomic<std::uint32_t> write_idx_;
}

#endif //_SCSP_FIXED_LENGTH_QUEUE_H_
