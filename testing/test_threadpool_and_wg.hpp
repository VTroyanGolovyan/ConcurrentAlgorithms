#include "../synchronize/scheduler/ThreadPool.hpp"
#include "../synchronize/wait_group/WaitGroup.hpp"

TEST(TestThreadPoolAndWG, Counter) {
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
    ASSERT_EQ(cnt.load(), 1000 * 10000);
}