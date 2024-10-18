#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include "../Mutex.hpp"
#include "../ConditionVariable.hpp"
#include "../blocking_queue/BlockingQueue.hpp"

#include "Task.hpp"
#include <vector>
#include <thread>

namespace synchronize {

namespace tp {

class ThreadPool {
public:
    explicit ThreadPool(size_t n_threads);
    void Submit(Task task);

    void Start();
    void Stop();

    static ThreadPool* GetCurrentThreadpool();
private:
    void WorkerBody();

    size_t n_threads_;
    std::vector<std::thread> threads_;
    BlockingQueue<Task> tasks_;
};

}

}

#endif
