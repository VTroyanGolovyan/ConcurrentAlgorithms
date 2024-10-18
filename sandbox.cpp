#include <iostream>
#include "synchronize/scheduler/ThreadPool.hpp"
#include "synchronize/wait_group/WaitGroup.hpp"
#include "synchronize/wait_group/WaitGroup.hpp"
#include "synchronize/future/Future.hpp"

int main() {

    synchronize::tp::ThreadPool tp(4);
    std::atomic<int> cnt = 0;
    tp.Start();
    synchronize::Promise<int> promise;

    synchronize::Future<int> future = promise.GetFuture();

    synchronize::WaitGroup wg;
    for (size_t i = 0; i < 1000; ++i) {
        wg.Add(1);
        tp.Submit(
            [&, k=i]() {
                for (size_t i = 0; i < 10000; ++i) {
                    ++cnt;
                    if (k == 5 && i == 1999) {
                        promise.SetValue(i);
                    }
                }
                wg.Done();
            }
        );
    }

    std::cout << future.Get() << std::endl;

    wg.Wait();
    std::cout << cnt << std::endl;
    tp.Stop();
    std::cout << cnt << std::endl;

    return 0; 
}