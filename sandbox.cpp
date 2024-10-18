#include <iostream>
#include "synchronize/scheduler/ThreadPool.hpp"
#include "synchronize/wait_group/WaitGroup.hpp"

int main() {

    synchronize::tp::ThreadPool tp(4);
    std::atomic<int> cnt = 0;
    tp.Start();

    synchronize::WaitGroup wg;
    for (size_t i = 0; i < 1000; ++i) {
        wg.Add(1);
        tp.Submit(
            [&]() {
                for (size_t i = 0; i < 10000; ++i) {
                    ++cnt;
                }
                wg.Done();
            }
        );
    }
    
    wg.Wait();
    std::cout << cnt;
    tp.Stop();
    std::cout << cnt;
    return 0;
}