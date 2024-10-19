
#ifndef SYNC_MUTEX_HPP
#define SYNC_MUTEX_HPP

#include <atomic>

namespace synchronize {

/** @brief Mutex, synchronization primitive that can be used to protect shared data */
class Mutex {
public:
    Mutex() = default;
    /** no copy-constructible */
    Mutex(const Mutex& /*other*/) = delete; 
    /** no copy-assignable */
    Mutex& operator=(const Mutex& /*other*/) = delete;

    /** @brief locks the mutex, blocks if the mutex is not available */
    void lock();
    /** @brief unlocks the mutex */
    void unlock();

private:
    uint32_t CAS(uint32_t expected, uint32_t new_value);

    static constexpr uint32_t kUnlocked = 0;
    static constexpr uint32_t kLockedWithNoWaiters = 1;
    static constexpr uint32_t kLockedWithWaiters = 2;

    std::atomic<uint32_t> state_{kUnlocked};
};

}

#endif
