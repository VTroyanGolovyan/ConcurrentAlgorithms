#include "SharedMutex.hpp"

#include <mutex>

namespace synchronize {

void SharedMutex::lock() {
    std::unique_lock<Mutex> lk(m_);
    enter_crit_section_.wait(lk, [&]() { return readers_ == 0 && !writer_; });
    writer_ = true;
}

void SharedMutex::unlock() {
    std::lock_guard<Mutex> lk(m_);
    writer_ = false;
    enter_crit_section_.notify_one();
}

void SharedMutex::lock_shared() {
    std::unique_lock<Mutex> lk(m_);
    enter_crit_section_.wait(lk, [&]() { return !writer_; });
    ++readers_;
}

void SharedMutex::unlock_shared() {
    std::lock_guard<Mutex> lk(m_);
    --readers_;
    enter_crit_section_.notify_one();
}

}