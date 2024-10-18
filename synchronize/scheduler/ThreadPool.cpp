#include "ThreadPool.hpp"


namespace synchronize {

namespace tp {

// pointer for current threadpool
thread_local ThreadPool* current_threadpool{nullptr};

ThreadPool::ThreadPool(size_t n_threads) : n_threads_(n_threads)  {}

void ThreadPool::Submit(Task task) {
    tasks_.Push(task);
}

void ThreadPool::Start() {
    for (size_t i = 0; i < n_threads_; ++i) {
        threads_.emplace_back([this]() {
            WorkerBody();
        });
    }
}

void ThreadPool::Stop() {
    tasks_.Close();
    for (auto& th : threads_) {
        th.join();
    }
}

void ThreadPool::WorkerBody() {
    std::optional<Task> current_task;
    current_threadpool = this;
    while ((current_task = tasks_.Pop())) {
        
        (*current_task)();
    }
    current_threadpool = nullptr;
} 

ThreadPool* ThreadPool::GetCurrentThreadpool() {
    return current_threadpool;
}

}

}
