#ifndef SYNC_SPIN_LOCK_HPP
#define SYNC_SPIN_LOCK_HPP

#include <atomic>

namespace synchronize {

class SpinLock {
    SpinLock() = default;
    SpinLock(const SpinLock& /*other*/) = delete;
    SpinLock& operator=(const SpinLock& /*other*/) = delete;

    void lock();

    void unlock();
private:
    static constexpr int kUnlocked = 0;
    static constexpr int kLocked = 1;
    std::atomic<uint32_t> state_{kUnlocked};
};

}

#endif
