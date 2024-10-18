#include "../synchronize/scheduler/ThreadPool.hpp"
#include "../synchronize/wait_group/WaitGroup.hpp"
#include "../synchronize/future/Future.hpp"

TEST(TestFuture, Counter) {
    synchronize::tp::ThreadPool tp(4);
    std::atomic<int> cnt = 0;

    synchronize::Promise<int> promise;
    synchronize::Future<int> future = promise.GetFuture();

    synchronize::Promise<int> promise2;
    synchronize::Future<int> future2 = promise2.GetFuture();

    tp.Start();
    
    synchronize::WaitGroup wg;
    for (size_t i = 0; i < 1000; ++i) {
        wg.Add(1);
        tp.Submit(
            [&, k=i]() {
                try {
                    for (size_t i = 0; i < 10000; ++i) {
                        ++cnt;
                        if (k == 42 && i == 42) {
                            promise.SetValue(42);
                        }
                        if (k == 84 && i == 84) {
                           throw std::runtime_error("TEST");
                        }
                    }
                } catch(...) {
                     promise2.SetException(std::current_exception());
                }
                wg.Done();
            }
        );
    }
    
    wg.Wait();
    std::cout << cnt;
    tp.Stop();
    ASSERT_EQ(future.Get(), 42);
    ASSERT_THROW(future2.Get(), std::runtime_error);
}