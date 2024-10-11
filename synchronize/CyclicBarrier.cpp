#include "CyclicBarrier.hpp"

namespace synchronize {

CyclicBarrier::CyclicBarrier(uint32_t count) : count_(count), current_wave_{0} {
    wawe_counters_ = {0, 0};
}

void CyclicBarrier::arrive_and_wait() {
    std::unique_lock<Mutex> lk(m_);
    uint32_t now_wave = current_wave_;
    ++wawe_counters_[now_wave];
    if (wawe_counters_[now_wave] == count_) {
        now_wave ^= 1;
        all_arrive_.notify_all();
    } else {
        all_arrive_.wait(lk, [&]() { return now_wave != current_wave_; });
        --wawe_counters_[now_wave];
    }
}

}
