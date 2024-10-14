#include "../synchronize/Mutex.hpp"
#include "../synchronize/ConditionVariable.hpp"

TEST(TestConditionVariable, PingPong) {
    synchronize::Mutex m;
    synchronize::ConditionVariable cv;
    size_t counter = 0;
    size_t sum = 0;
    size_t th_num_increments = 100000;
    std::thread th1([&]() {
        size_t wait_counter = 0;
        for (size_t i = 0; i < th_num_increments; ++i) {
            std::unique_lock<synchronize::Mutex> lk(m);
            cv.wait(lk, [&]() { return counter == wait_counter; });
            ++counter;
            sum += counter;
            wait_counter += 2;
            cv.notify_one();
        }
    });

    std::thread th2([&]() {
        size_t wait_counter = 1;
        for (size_t i = 0; i < th_num_increments; ++i) {
            std::unique_lock<synchronize::Mutex> lk(m);
            cv.wait(lk, [&]() { return counter == wait_counter; });
            ++counter;
            sum += counter;
            wait_counter += 2;
            cv.notify_one();
        }
        
    });

    th1.join();
    th2.join();

    ASSERT_EQ(counter, 2 * th_num_increments);
    ASSERT_EQ(2 * sum, 2 * th_num_increments * (2 * th_num_increments + 1));
}
