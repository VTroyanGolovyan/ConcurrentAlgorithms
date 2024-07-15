#pragma once

template <typename T, typename Backoff> requires std::invocable<Backoff>
MichaelScottQueue<T, Backoff>::MichaelScottQueue() {
    auto sentinel = new Node(T());
    head_.store(sentinel);
    tail_.store(sentinel);
}

template <typename T, typename Backoff> requires std::invocable<Backoff>
std::optional<T> MichaelScottQueue<T, Backoff>::TryPop() {

    Backoff backoff;

    auto mutator = hazard::Manager::Get().MakeMutator();

    auto head_guard = mutator.GetHazardPtr(0);
    auto next_guard = mutator.GetHazardPtr(1);

    while (true) {
        auto head = head_guard.Protect(head_);
        
        if (head_.load() != head) {
            backoff();
            continue;
        }

        auto next = next_guard.Protect(head->next);

        if (next == nullptr) {
            return {};
        }

        auto tail = tail_.load();
        if (head == tail) {
            tail_.compare_exchange_strong(tail, next);
            backoff();
            continue;
        }

        if (head_.compare_exchange_strong(head, next)) {
            T res = next->value;
            mutator.Retire(head);
            return res;
        }

        backoff();
    }
    
}

template <typename T, typename Backoff> requires std::invocable<Backoff>
void MichaelScottQueue<T, Backoff>::Push(const T& value) {
    Backoff backoff;

    Node* new_tail = new Node(value);

    auto mutator = hazard::Manager::Get().MakeMutator();
    auto tail_guard = mutator.GetHazardPtr(0);

    while (true) {
        auto tail = tail_guard.Protect(tail_);
        auto next = tail->next.load();
        if (tail != tail_.load()) {
            backoff();
            continue;
        }
        if (next != nullptr) {
            tail_.compare_exchange_weak(tail, next);
            continue;
        }
        Node* temp = nullptr;
        if (tail->next.compare_exchange_strong(temp, new_tail)) {
            tail_.compare_exchange_strong(tail, new_tail);
            break;
        }
    }
}

template <typename T, typename Backoff> requires std::invocable<Backoff>
MichaelScottQueue<T, Backoff>::~MichaelScottQueue() {
    while (head_ != nullptr) {
        Node* to_remove = head_.load();
        head_ = to_remove->next.load();
        delete to_remove;
    } 
}
    
   
