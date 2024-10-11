#ifndef SYNC_CYCLIC_BARRIER_HPP
#define SYNC_CYCLIC_BARRIER_HPP

#include <array>
#include <mutex>
#include "Mutex.hpp"
#include "ConditionVariable.hpp"

namespace synchronize {
    
class CyclicBarrier {
public:
    CyclicBarrier(uint32_t count);

    void arrive_and_wait();

private:
    Mutex m_;
    ConditionVariable all_arrive_;

    uint32_t count_;
    uint32_t current_wave_{0};
    std::array<uint32_t, 2> wawe_counters_; 
};

}
#endif
