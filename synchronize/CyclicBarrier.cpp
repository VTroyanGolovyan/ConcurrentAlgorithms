#include "CyclicBarrier.hpp"

namespace synchronize {

CyclicBarrier::CyclicBarrier(uint32_t count) : count_(count), current_wave_(0) {
    wave_counters_ = {0, 0};
}

void CyclicBarrier::arrive_and_wait() {
    std::unique_lock<synchronize::Mutex> lk(m_);
    uint32_t now_wave = current_wave_;
    ++wave_counters_[now_wave];
    if (wave_counters_[now_wave] == count_) {
        current_wave_ ^= 1;
        wave_counters_[current_wave_] = 0;
        all_arrive_.notify_all();
    } else {
        all_arrive_.wait(lk, [&]() { return now_wave != current_wave_; });
    }
}

}
