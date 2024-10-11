
#include "sync/Mutex.hpp"

#include <memory>
#include <vector>
#include <thread>
#include <iostream>
#include <cassert>

void test_lock_unlock() {
    int x = 0;
    sync::Mutex m;
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
    th1.join();
    th2.join();
    std::cout << x << std::endl;
}

int main() {

    test_lock_unlock();

    return 0;    
}