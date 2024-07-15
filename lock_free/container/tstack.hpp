#ifndef LOCK_FREE_STACK_HPP
#define LOCK_FREE_STACK_HPP

#include "../memory/hazard/HPManager.hpp"
#include "../backoff/EmptyBackoff.hpp"

#include <optional>
#include <concepts>

/*
*   Lock-free Treiber Stack
*   Multi-producer, multi-consumer stack.
*   @tparam T - values type
*   @tparam Backoff - backoff strategy type
*/
template <typename T, typename Backoff = EmptyBackoff> requires std::invocable<Backoff>
class LockFreeStack {
  struct Node {
    Node(T&& x) : value(std::forward<T>(x)) {}
    T value;
    Node* next{nullptr};
  };

 public:
  LockFreeStack() = default;

  /*
  * @brief inserts element at the top, complexity O(1)
  * @param value - the value of the element to push
  */
  void Push(T value);

  /*
  * @brief Removes the top element, if it's possible
  * @return value - removed element's value, if success, nullopt otherwise
  */
  std::optional<T> TryPop();

  ~LockFreeStack();

 private:
  std::atomic<Node*> top_{nullptr};

};

#include "./impl/tstack_impl.hpp"

#endif
