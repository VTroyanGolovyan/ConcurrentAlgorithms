#include "../synchronize/SharedMutex.hpp"

TEST(TestSharedMutex, Counter) {
    int x = 0;
    std::atomic<size_t> y = 0;
    synchronize::SharedMutex m;
    std::vector<std::thread> ths;
    for (int i = 0; i < 2; ++i) {
        ths.emplace_back([&]() {
            for (size_t i = 0; i < 100000; ++i) {
                m.lock();
                ++x;
                m.unlock();
            }
        });
    }

    std::atomic<size_t> b;
    ths.emplace_back([&]() {
        for (size_t i = 0; i < 100000; ++i) {
            m.lock_shared();
            b += x;
            m.unlock_shared();
        }
    });

    for (auto& th : ths) {
        th.join();
    }
    ASSERT_EQ(x, 200000);
}