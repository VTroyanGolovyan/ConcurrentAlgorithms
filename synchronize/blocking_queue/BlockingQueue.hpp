#ifndef BLOCKING_QUEUE_HPP
#define BLOCKING_QUEUE_HPP

#include "../Mutex.hpp"
#include "../ConditionVariable.hpp"

#include <deque>

namespace synchronize {

template <typename T>
class BlockingQueue {
public:
    BlockingQueue() = default;

    void Push(T value);
    std::optional<T> Pop();
    void Close();

private:
    Mutex m_;
    ConditionVariable any_data_or_close_;
    std::deque<T> queue_;
    bool is_closed_{false};
};

}

#include "BlockingQueue.impl"

#endif
