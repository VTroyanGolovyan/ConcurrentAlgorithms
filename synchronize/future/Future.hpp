#ifndef FURURE_HPP
#define FURURE_HPP

#include "../Mutex.hpp"
#include "../ConditionVariable.hpp"

#include <exception>

namespace synchronize {

enum class FutureStatus {
    done,
    undone
};

template <typename T>
struct SharedState {
    T data;
    Mutex m;
    ConditionVariable cv;
    std::exception_ptr exception_ptr;
    FutureStatus status{FutureStatus::undone};
};

template <typename T>
class Future {
public:
    Future(SharedState<T>* state) : state_(state) {}
    T& Get() {
        std::unique_lock<Mutex> lk(state_->m);
        state_->cv.wait(lk, [&](){ return state_->status == FutureStatus::done; });
        if (state_->exception_ptr) {
             std::rethrow_exception(state_->exception_ptr);
        }
        return state_->data;
    }

private:
    SharedState<T>* state_;
};

template <typename T>
class Promise {
public:
    void SetValue(const T& value) {
        std::lock_guard<Mutex> lk(state_.m);
        state_.data = value;
        state_.status = FutureStatus::done;
        state_.cv.notify_one();
    }

    void SetException(std::exception_ptr ptr) {
        std::lock_guard<Mutex> lk(state_.m);
        state_.exception_ptr = ptr;
        state_.status = FutureStatus::done;
        state_.cv.notify_one();
    }

    Future<T> GetFuture() {
        return Future<T>(std::addressof(state_));
    }
private:
    SharedState<T> state_;
};

}

#endif