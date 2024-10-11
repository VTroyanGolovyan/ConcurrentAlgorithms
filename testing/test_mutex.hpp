#include "../synchronize/Mutex.hpp"

TEST(TestMutex, Counter) {
    int x = 0;
    synchronize::Mutex m;
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
    th1.join();
    th2.join();
    ASSERT_EQ(x, 200000);
}
