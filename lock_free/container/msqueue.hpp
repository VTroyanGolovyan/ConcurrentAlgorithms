#ifndef LOCK_FREE_QUEUE_HPP
#define LOCK_FREE_QUEUE_HPP

#include "../memory/hazard/HPManager.hpp"
#include "../backoff/EmptyBackoff.hpp"

#include <optional>
#include <concepts>

/*
*   Lock-free Michael-Scott Queue
*   Multi-producer, multi-consumer stack.
*   @tparam T - values type
*   @tparam Backoff - backoff strategy type
*/
template <typename T, typename Backoff = EmptyBackoff> requires std::invocable<Backoff>
class MichaelScottQueue {
public:
    struct Node {
        T value;
        std::atomic<Node*> next;
        Node(const T& value) : value(value), next(nullptr) {}
    };

    MichaelScottQueue();

    /*
    * @brief inserts element at the end of queue, complexity O(1)
    * @param value - the value of the element to push
    */
    void Push(const T& value);

    /*
    * @brief Removes the front element, if it's possible
    * @return value - removed element's value, if success, nullopt otherwise
    */
    std::optional<T> TryPop();

    ~MichaelScottQueue();
    
    private:
        std::atomic<Node*> head_;
        std::atomic<Node*> tail_;
};

#include "./impl/msqueue_impl.hpp"

#endif