#ifndef SYNC_LATCH_HPP
#define SYNC_LATCH_HPP

#include "Mutex.hpp"
#include "ConditionVariable.hpp"

namespace synchronize {

/**
* @brief The latch class is a downward counter which can be used to synchronize threads. 
*        The value of the counter is initialized on creation. 
*        Threads may block on the latch until the counter is decremented to zero. 
*        There is no possibility to increase or reset the counter, which makes the latch a single-use barrier.
*/
class Latch {
public:

    explicit Latch(uint32_t cnt);
    Latch(const Latch& /*other*/) = delete; // non copiable

    void count_down();

    void wait();

    void arrive_and_wait();

    bool try_wait();

private:
    ConditionVariable other_threads_;
    Mutex m_;
    uint32_t counter_;
};

}

#endif