#ifndef SYNC_SEMAPHORE_HPP
#define SYNC_SEMAPHORE_HPP

#include "Mutex.hpp"
#include "ConditionVariable.hpp"

#include <cstdint>
#include <mutex>

namespace synchronize {

/**
*  @brief Semaphore is a lightweight synchronization primitive that can control access to a shared resource. Unlike a std::mutex, a counting_semaphore allows more than one concurrent access to the same resource, for at least LeastMaxValue concurrent accessors. 
*/
template <uint32_t LeastMaxValue>
class Semaphore {
public:
    Semaphore() = default;
    // no copy-constructible
    Semaphore(const Semaphore& /*other*/) = default;
    // no copy-assignable
    Semaphore& operator=(const Semaphore& /*other*/) = default;
    // @brief Decrements the internal counter or blocks until it can
    void Aquire() {
        std::unique_lock<Mutex> lk(m_);
        non_zero_counter_.wait(lk, [&]() { return counter_ > 0; });
        --counter_;
    }
    
    // @brief Increments the internal counter and unblocks acquirers
    void Release() {
        std::lock_guard<Mutex> lk(m_);
        ++counter_;
        non_zero_counter_.notify_all();
    }
    
private:
    Mutex m_;
    ConditionVariable non_zero_counter_;
    size_t counter_{LeastMaxValue};

};

using BinarySemaphore = Semaphore<1>;

}

#endif
