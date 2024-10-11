#include "SpinLock.hpp"

namespace synchronize {

void SpinLock::lock() {
    while (state_.exchange(kLocked, std::memory_order_acquire) != kUnlocked) {
        // to optimize cache coherency mechanizm
        while (state_.load(std::memory_order_relaxed) == kLocked) {
        }
    }
}

void SpinLock::unlock() {
    state_.store(kUnlocked, std::memory_order_release);
}

}
