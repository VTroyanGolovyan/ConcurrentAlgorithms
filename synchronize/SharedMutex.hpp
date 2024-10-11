#ifndef SYNC_SHARED_MUTEX_HPP
#define SYNC_SHARED_MUTEX_HPP

#include "Mutex.hpp"
#include "ConditionVariable.hpp"
#include <mutex>

namespace synchronize {

class SharedMutex {
public:
    SharedMutex() = default;

    // no copy-constructible
    SharedMutex(const SharedMutex& /*other*/) = delete; // non copyable
    // no copy-assignable
    SharedMutex& operator=(const SharedMutex& /*other*/) = delete;

    // @brief Exlusive ownership
    void lock();

    void unlock();

    // @brief Shared ownership
    void lock_shared();

    void unlock_shared();

private:
  size_t readers_{0};
  bool writer_{false};

  ConditionVariable enter_crit_section_;
  Mutex m_;
};

}

#endif
