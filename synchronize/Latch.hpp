#ifndef SYNC_LATCH_HPP
#define SYNC_LATCH_HPP

#include "Mutex.hpp"
#include "ConditionVariable.hpp"

namespace synchronize {

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