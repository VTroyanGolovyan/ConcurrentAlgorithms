#include "Fiber.hpp"


namespace fiber {

using Body = std::function<void()>;

thread_local Fiber* current_fiber{nullptr};

Fiber::Fiber(Body task) : task_(std::move(task)), coro_([this](auto self){
    RunBody(self);
})  {
}

Fiber* Fiber::Fiber::Self() {
    return current_fiber;
}

void Fiber::RunBody(coro::SuspendContext& ctx) {
    current_fiber = this;
    ctx_ = ctx;
    task_();
    current_fiber = nullptr;
}

void Yield() {
    Fiber* now = Fiber::Self();
    synchronize::tp::ThreadPool::GetCurrentThreadpool()->Submit([now]() {
        while (now->coro_.Running()) {
        }
        if (now->coro_.IsCompleted()) {
            current_fiber = nullptr;
            delete now;
        } else {
            current_fiber = now;
            now->coro_.Resume();
        }
    });
    now->ctx_->Suspend();
}

void Go(synchronize::tp::ThreadPool& scheduler, Body body) {
    Fiber* fiber = new Fiber(body);
    scheduler.Submit([fiber]() {
        current_fiber = fiber;
        fiber->coro_.Resume();
        current_fiber = nullptr;
    });
}

}