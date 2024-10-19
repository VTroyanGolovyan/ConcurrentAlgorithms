#ifndef SYNC_SPIN_LOCK_HPP
#define SYNC_SPIN_LOCK_HPP

#include <atomic>

namespace synchronize {

/**
* A spinlock is a low-level synchronization primitive used 
* in multiprocessor systems to implement mutual exclusion of 
* critical sections of code using an active wait loop.
*/
class SpinLock {
    SpinLock() = default;
    // non copy constructible
    SpinLock(const SpinLock& /*other*/) = delete;
    // non coppy assignable
    SpinLock& operator=(const SpinLock& /*other*/) = delete;

    /* @brief locks the spin lock */
    void lock();

    /* @brief unlocks the spin lock */
    void unlock();
private:
    static constexpr int kUnlocked = 0;
    static constexpr int kLocked = 1;
    std::atomic<uint32_t> state_{kUnlocked};
};

}

#endif
