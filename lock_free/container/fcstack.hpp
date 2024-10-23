// Bad code, TODO: fix it

#include <memory>
#include <vector>
#include <thread>
#include <iostream>
#include <cassert>
#include <atomic>
#include <random>
#include <chrono>


#define threads 30

std::atomic<size_t> counter_fc = 0;
thread_local std::atomic<size_t> fc_thread_id = counter_fc.fetch_add(1);

template <typename T>
class FCStack {
    struct Node {
        Node(T&& x) : value(std::forward<T>(x)) {}
        T value;
        Node* next{nullptr};
    };

    enum Operation {
        empty,
        push,
        pop
    };

    struct FlatCombiningAnounce {
        std::atomic<int> finished;
        std::atomic<Operation> op{empty};
        std::optional<T> data;
        std::atomic<std::time_t> stamp;
    };

    static FlatCombiningAnounce anounces[threads];
public:
    void Push(const T& value) {
        auto& anounce = anounces[fc_thread_id];
        anounce.stamp = std::time(nullptr);
        anounce.data = value;
        anounce.op = push;
        anounce.finished = false;
        while (true) {
            std::unique_lock lk(m_, std::try_to_lock);
            if (lk.owns_lock()) {
                locked_.store(true);
                FlatCombining();
                locked_.store(false);
                break;
            } else {
                while (!anounce.finished && locked_) {
                    usleep(30);
                }
                if (anounce.finished) {
                    break;
                }
            }
        }
        
        anounce.op = empty;
    }

    std::optional<T> TryPop() {
        auto& anounce = anounces[fc_thread_id];
        anounce.stamp = std::time(nullptr);
        anounce.op = pop;
        anounce.finished = false;
        while (true) {
            std::unique_lock lk(m_, std::try_to_lock);
            
            if (lk.owns_lock()) {
                locked_.store(true);
                FlatCombining();
                locked_.store(false);
                break;
            } else {
                while (!anounce.finished  && locked_) {
                    usleep(30);
                }
                if (anounce.finished) {
                    break;
                }
            }
        }

        anounce.op = empty;
        return anounce.data;
    }
private:
    void FlatCombining() {
        FlatCombiningAnounce* process_anounces[threads];
        size_t cnt = 0;
        for (auto& anounce : anounces) {
            if (anounce.op == empty) {
                continue;
            }
            if (!anounce.finished) {
                process_anounces[cnt++] = &anounce;
            }
        }
        std::sort(process_anounces, process_anounces + cnt, [](const auto& lhs, const auto& rhs) {
            return lhs->stamp < rhs->stamp;
        });

        for (size_t i = 0; i < cnt; ++i) {
            if (process_anounces[i]->op == push) {
                Node* new_top = new Node(std::move(process_anounces[i]->data.value()));
                new_top->next = top_;
                top_ = new_top;
            } else if (process_anounces[i]->op == pop) {
                if (top_ != nullptr) {
                    Node* old_top = top_;
                    process_anounces[i]->data = std::move(old_top->value);
                    top_ = top_->next;
                } else {
                    process_anounces[i]->data = std::nullopt;
                }
            }
            process_anounces[i]->finished = true;
        }
    }

    std::mutex m_;
    std::atomic<bool> locked_;
    Node* top_{nullptr};

};

template <typename T>
FCStack<T>::FlatCombiningAnounce FCStack<T>::anounces[threads]{};

#endif