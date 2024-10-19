#ifndef SYNC_SHARED_MUTEX_HPP
#define SYNC_SHARED_MUTEX_HPP

#include "Mutex.hpp"
#include "ConditionVariable.hpp"
#include <mutex>

namespace synchronize {

/** 
* @brief The SharedMutex class is a synchronization primitive that can be used to protect shared data from being simultaneously accessed by multiple threads. In contrast to other mutex types which facilitate exclusive access, a shared_mutex has two levels of access:
*          shared - several threads can share ownership of the same mutex.
*          exclusive - only one thread can own the mutex.
*        If one thread has acquired the exclusive lock (through lock, try_lock), no other threads can acquire the lock (including the shared).
*        If one thread has acquired the shared lock (through lock_shared, try_lock_shared), no other thread can acquire the exclusive lock, but can acquire the shared lock.
*        Only when the exclusive lock has not been acquired by any thread, the shared lock can be acquired by multiple threads.
*        Within one thread, only one lock (shared or exclusive) can be acquired at the same time.
*        Shared mutexes are especially useful when shared data can be safely read by any number of threads simultaneously, but a thread may only write the same data when no other thread is reading or writing at the same time.
*/
class SharedMutex {
public:
    SharedMutex() = default;

    // no copy-constructible
    SharedMutex(const SharedMutex& /*other*/) = delete; // non copyable
    // no copy-assignable
    SharedMutex& operator=(const SharedMutex& /*other*/) = delete;

    // @brief Exlusive ownership
    void lock();

    // @brief Unlock exlusive ownership
    void unlock();

    // @brief Shared ownership
    void lock_shared();

    // @brief Unlock shared ownership
    void unlock_shared();

private:
  size_t readers_{0};   // reader number
  bool writer_{false};  // witer number

  ConditionVariable enter_crit_section_;
  Mutex m_;
};

}

#endif
