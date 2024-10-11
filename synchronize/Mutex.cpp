#include <atomic>
#include "Mutex.hpp"

namespace synchronize {

void Mutex::lock() {
    while (CAS(kUnlocked, kLockedWithNoWaiters) != kUnlocked) {
        while (CAS(kLockedWithNoWaiters, kLockedWithWaiters) != kUnlocked) {
            state_.wait(kLockedWithWaiters);
        }
    }
}

void Mutex::unlock() {
    if (state_.exchange(kUnlocked) == kLockedWithWaiters) {
        state_.notify_one();
    }
}

uint32_t Mutex::CAS(uint32_t expected, uint32_t new_value) {
    state_.compare_exchange_strong(expected, new_value);
    return expected;
}

}
