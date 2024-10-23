#ifndef FIBER_HPP
#define FIBER_HPP

#include "../scheduler/ThreadPool.hpp"
#include "../coro/Coroutine.hpp"
#include <iostream>

namespace fiber {

using Body = std::function<void()>;

class Fiber {
    friend void Go(synchronize::tp::ThreadPool& scheduler, Body fiber);
    friend void Yield();
private:
    Fiber(Body task);

    static Fiber* Self();
private:
    void RunBody(coro::SuspendContext& ctx);

    Body task_;
    std::optional<coro::SuspendContext> ctx_;
    coro::StackfullCoroutine coro_;
};

void Yield();

void Go(synchronize::tp::ThreadPool& scheduler, Body body);

}

#endif
