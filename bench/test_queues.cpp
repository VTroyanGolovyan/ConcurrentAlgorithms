
#include "lock_free/container/msqueue.hpp"
#include "lock_free/container/tstack.hpp"

#include "lock_free/backoff/ExponentioalBackoff.hpp"

#include <memory>
#include <vector>
#include <thread>
#include <iostream>
#include <cassert>

#define N 100000

template <typename QType>
void benchmark() {
    clock_t start = clock();
    QType* q = new QType();

    std::vector<std::thread> ths;
    

    for (size_t i = 0; i < 14; ++i) {
        auto task = [num=i, &q](){
            for (size_t i = num * N; i < num * N  + N; ++i) {
                q->Push(i);
            }
        };
        ths.emplace_back(task);
    }
    
    std::atomic<size_t> sum = 0;

    for (size_t i = 0; i < 14; ++i) {
        auto task = [&q, &sum](){
            for (size_t i = 0; i <  N; ++i) {
                auto x = q->TryPop();
                if (x) {
                    sum += x.value();
                }   
            }
        };
        ths.emplace_back(task);
    }
    for (auto& t : ths) {
        t.join();
    }

    while (auto x = q->TryPop())
    {
        if (x) {
            sum += x.value();
        }
    } 

    clock_t end = clock();
    std::cout << static_cast<double>(end - start) / CLOCKS_PER_SEC << "\n";

    size_t s = 0;
    for (size_t i = 0; i  < 14 * N; ++i) {
        s += i;
    }

    std::cout << sum << " " << s << std::endl;
    assert(sum == s);
    
    delete q;
}



int main() {

    benchmark<LockFreeStack<int>>();
    benchmark<MichaelScottQueue<int>>();
    return 0;    
}