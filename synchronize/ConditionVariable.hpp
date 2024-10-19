#ifndef SYNC_CONDITION_VARIABLE_HPP
#define SYNC_CONDITION_VARIABLE_HPP

#include <atomic>

namespace synchronize {

/**
*  @brief ConditionVariable is a synchronization primitive used with a Mutex to 
*         block one or more threads until another thread both modifies a shared variable (the condition) and notifies the ConditionVariable.
*/
class ConditionVariable {
public:
    ConditionVariable() = default;
    ConditionVariable(const ConditionVariable& /*other*/) = delete;

    template <typename Lockable>
    void wait(Lockable& lock) {
        uint32_t value = wait_.load();
        lock.unlock();
        wait_.wait(value);
        lock.lock();
    }

    template<typename Lockable, typename Predicate>
    void wait(Lockable& lock, Predicate pred) {
        while (!pred()) {
            wait(lock);
        }
    }

    void notify_all() {
        wait_.fetch_add(1);
        wait_.notify_all();
    }

    void notify_one() {
        wait_.fetch_add(1);
        wait_.notify_one();
    }
private:
    std::atomic<uint32_t> wait_{0};
};

}

#endif
