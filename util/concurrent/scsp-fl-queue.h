#ifdef _SCSP_FIXED_LENGTH_QUEUE_H_

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

    T pop() {
    	return T;
    }
    
    bool is_full() {
    	return false;
    }
    
    bool is_emty() {
    	return false;
    }
    
    void clear() {
    
    }
    
    std::uint32_t capacity() {
    	return 0;
    }
private:
    std::uint32_t capacity_;
}

#endif //_SCSP_FIXED_LENGTH_QUEUE_H_
