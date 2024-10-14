#ifndef SYNC_SEMAPHORE_HPP
#define SYNC_SEMAPHORE_HPP

#include "Mutex.hpp"
#include "ConditionVariable.hpp"

#include <cstdint>
#include <mutex>

namespace synchronize {

template <uint32_t LeastMaxValue>
class Semaphore {
public:
    Semaphore() = default;

    void Aquire() {
        std::unique_lock<Mutex> lk(m_);
        non_zero_counter_.wait(lk, [&]() { return counter_ > 0; });
        --counter_;
    }

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
