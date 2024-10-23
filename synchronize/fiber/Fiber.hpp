#ifndef FIBER_HPP
#define FIBER_HPP

#include "../scheduler/ThreadPool.hpp"
#include "../coro/Coroutine.hpp"

#include <exception>
#include <stdexcept>

namespace fiber {

using Body = std::function<void()>;

class Fiber {
    friend void Go(synchronize::tp::ThreadPool& scheduler, Body fiber);
    friend void Go(Body body);
    friend void Yield();
    friend void JumpBackToScheduler(Fiber* fiber);
    friend void Suspend();
private:
    Fiber(synchronize::tp::ThreadPool& scheduler, Body task);
public:
    static Fiber* Self();
private:
    void RunBody(coro::SuspendContext& ctx);

    Body task_;
    std::optional<coro::SuspendContext> ctx_;
    coro::StackfullCoroutine coro_;
    synchronize::tp::ThreadPool* scheduler_;
    std::exception_ptr exception_;
};

void Yield();

void Go(synchronize::tp::ThreadPool& scheduler, Body body);

void Go(Body body);

void Yield();

void Suspend();

void JumpBackToScheduler(Fiber* fiber);

}

#endif
