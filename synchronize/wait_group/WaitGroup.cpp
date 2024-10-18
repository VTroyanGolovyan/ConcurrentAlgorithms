#include "WaitGroup.hpp"

#include <atomic>

namespace synchronize {
/*
* Use it for task waiting in ThreadPool
*/

WaitGroup::WaitGroup(uint32_t task_cnt) : task_count_(task_cnt) {}

void WaitGroup::Wait() {
    uint32_t curr_value;
    while ((curr_value = task_count_.load()) != 0) {
        task_count_.wait(curr_value); // sleep until notify or wake up
    }
}

void WaitGroup::Add(uint32_t count) {
    task_count_ += count;
}

void WaitGroup::Done() {
    task_count_--;
    task_count_.notify_all();
}

}