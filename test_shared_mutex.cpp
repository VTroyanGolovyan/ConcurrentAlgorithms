#include "sync/SharedMutex.hpp"
#include <iostream>
#include <thread>

int main() {

    int x = 0;
    std::atomic<size_t> y = 0;
    sync::SharedMutex m;
    std::thread th1([&]() {
        for (size_t i = 0; i < 10000000; ++i) {
            m.lock();
            ++x;
            m.unlock();
        }
    });
    std::thread th2([&]() {
        for (size_t i = 0; i < 10000000; ++i) {
            m.lock();
            ++x;
            m.unlock();
        }
    });

    std::atomic<size_t> b;
    std::thread th3([&]() {
        for (size_t i = 0; i < 10000000; ++i) {
            m.lock_shared();
            b += x;
            m.unlock_shared();
        }
    });

    th1.join();
    th2.join();
    th3.join();
    
    std::cout << x << std::endl;

    return 0;
}