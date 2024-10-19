#ifndef SYNC_CYCLIC_BARRIER_HPP
#define SYNC_CYCLIC_BARRIER_HPP

#include <array>
#include <mutex>
#include "Mutex.hpp"
#include "ConditionVariable.hpp"

namespace synchronize {

/**
* @brief The class CyclicBarrier provides a thread-coordination mechanism that blocks a group of threads of known size until all threads in that group have reached the barrier. 
         Unlike Latch, barriers are reusable
*/
class CyclicBarrier {
public:
    CyclicBarrier(uint32_t count);

    void arrive_and_wait();

private:
    synchronize::Mutex m_;
    synchronize::ConditionVariable all_arrive_;

    uint32_t count_;
    uint32_t current_wave_;
    std::array<uint32_t, 2> wave_counters_; 
};

}
#endif
