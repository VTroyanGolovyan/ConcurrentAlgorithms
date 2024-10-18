#pragma once

template <typename T, typename Backoff> requires std::invocable<Backoff>
void LockFreeStack<T, Backoff>::Push(T value) {
    Backoff backoff;

    Node* new_node = new Node(std::move(value));
    new_node->next = top_.load();

    while (!top_.compare_exchange_weak(new_node->next, new_node)) {
      backoff();
    }
}

template <typename T, typename Backoff> requires std::invocable<Backoff>
std::optional<T> LockFreeStack<T, Backoff>::TryPop() {
    auto mutator = hazard::Manager::Get().MakeMutator();
    Backoff backoff;

    auto top_guard = mutator.GetHazardPtr(0);

    while (true) {
        Node* curr_top = top_guard.Protect(top_);

        if (curr_top == nullptr) {
            return std::nullopt;
        }

        if (top_.compare_exchange_weak(curr_top, curr_top->next)) {
            T value = std::move(curr_top->value);
            top_guard.Reset();
            mutator.Retire(curr_top);
            return value;
        }

        backoff();
    }
}

template <typename T, typename Backoff> requires std::invocable<Backoff>
LockFreeStack<T, Backoff>::~LockFreeStack() {
Node* curr = top_.load();
    while (curr != nullptr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
}
