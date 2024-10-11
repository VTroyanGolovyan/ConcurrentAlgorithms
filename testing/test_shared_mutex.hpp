#include "../synchronize/SharedMutex.hpp"

TEST(TestSharedMutex, Counter) {
    int x = 0;
    std::atomic<size_t> y = 0;
    synchronize::SharedMutex m;
    std::thread th1([&]() {
        for (size_t i = 0; i < 100000; ++i) {
            m.lock();
            ++x;
            m.unlock();
        }
    });
    std::thread th2([&]() {
        for (size_t i = 0; i < 100000; ++i) {
            m.lock();
            ++x;
            m.unlock();
        }
    });

    std::atomic<size_t> b;
    std::thread th3([&]() {
        for (size_t i = 0; i < 100000; ++i) {
            m.lock_shared();
            b += x;
            m.unlock_shared();
        }
    });

    th1.join();
    th2.join();
    th3.join();
    ASSERT_EQ(x, 200000);
}