
#include "synchronize/fiber/Fiber.hpp"
#include "synchronize/scheduler/ThreadPool.hpp"
#include "synchronize/wait_group/WaitGroup.hpp"
#include "synchronize/fiber/io/io.hpp"
#include <iostream>
#include <functional>
#include <cassert>
#include <memory>
#include <chrono>

int main() {

  synchronize::tp::ThreadPool scheduler(4);
  fiber::IoService io(9000);

  scheduler.Start();

  fiber::Go(scheduler, [&] {
    while (true) {
      auto socket_ptr = io.Accept();
      fiber::Go([&io, socket_ptr]() mutable {
        while (true) {
          auto res = io.ReadSome(*socket_ptr);
          io.Write(*socket_ptr, res);
        }
      });
    }

  });
  
  io.RunService();
  scheduler.Stop();

  return 0;
}