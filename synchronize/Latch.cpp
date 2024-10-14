#include <mutex>
#include "Latch.hpp"

namespace synchronize {

Latch::Latch(uint32_t cnt) : counter_(cnt) {}

void Latch::count_down() {
    std::lock_guard<Mutex> lk(m_);
    counter_ -= 1;
    if (counter_ == 0) {
        other_threads_.notify_all();
    }
}

void Latch::wait() {
    std::unique_lock<Mutex> lk(m_);
    other_threads_.wait(lk, [&]() { return counter_ == 0; });
}

void Latch::arrive_and_wait() {
    std::unique_lock<Mutex> lk(m_);
    counter_ -= 1;
    if (counter_ == 0) {
        other_threads_.notify_all();
    } else {
        other_threads_.wait(lk, [&]() { return counter_ == 0; });
    }
}

bool Latch::try_wait() {
    std::lock_guard<Mutex> lk(m_);
    return counter_ == 0; 
}

}