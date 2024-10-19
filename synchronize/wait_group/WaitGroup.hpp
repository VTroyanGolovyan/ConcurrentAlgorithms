#ifndef WAIT_GROUP_HPP
#define WAIT_GROUP_HPP


#include <atomic>

namespace synchronize {
/**
* Use it for task finish waiting in ThreadPool
*/
class WaitGroup {
public:
    explicit WaitGroup(uint32_t task_cnt = 0);
    void Wait();
    void Add(uint32_t count);
    void Done();
private:
    std::atomic<uint32_t> task_count_;
};

}

#endif
