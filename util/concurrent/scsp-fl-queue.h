#ifdef _SCSP_FIXED_LENGTH_QUEUE_H_

template<typename T>
struct SCSPFixedLengthQueue {
    SCSPFixedLengthQueue(const SCSPFixedLengthQueue&) = delete;
    SCSPFixedLengthQueue& operator=(const SCSPFixedLengthQueue&) = delete;
    SCSPFixedLengthQueue(const SCSPFixedLengthQueue&&) = delete;
    SCSPFixedLengthQueue& operator=(const SCSPFixedLengthQueue&&) = delete;
    
    SCSPFixedLengthQueue(std::uint32_t size) {
    
    }
    
    ~SCSPFixedLengthQueue() {
    
    }
private:
    std::uint32_t size_;
}

#endif //_SCSP_FIXED_LENGTH_QUEUE_H_
