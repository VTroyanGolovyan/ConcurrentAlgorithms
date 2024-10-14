#include "../synchronize/Semaphore.hpp"

TEST(TestSemaphore, CounterLotWriters) {
    for (int j = 2; j <= 4; j += 2) {
        synchronize::BinarySemaphore sem;
        int x = 0;
        std::vector<std::thread> ths;
        for (int i = 0; i < j; ++i) {
            ths.emplace_back([&]() {
                for (size_t i = 0; i < 100000; ++i) {
                    sem.Aquire();
                    ++x;
                    sem.Release();
                }
            });
        }
        for (auto& th : ths) {
            th.join();
        }
        ASSERT_EQ(x, j * 100000);
    }
}
