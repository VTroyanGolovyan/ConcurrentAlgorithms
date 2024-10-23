
#include "synchronize/fiber/Fiber.hpp"
#include "synchronize/scheduler/ThreadPool.hpp"
#include "synchronize/wait_group/WaitGroup.hpp"
#include <iostream>
#include <functional>
#include <cassert>

int main() {
  synchronize::tp::ThreadPool scheduler{2};
  scheduler.Start();

  synchronize::WaitGroup wg;

  std::atomic<int> x{0};
  for (size_t i = 0; i < 400000; ++i) {
    wg.Add(1);
    fiber::Go(scheduler, [&wg, &scheduler, &x] {
      for (size_t j = 0; j < 100; ++j) {
        ++x;
        fiber::Yield();
      }
      wg.Done();
    });
  }

  wg.Wait();
  std::cout << x.load();
  scheduler.Stop();

  return 0;
}