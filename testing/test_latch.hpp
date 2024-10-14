#include "../synchronize/Latch.hpp"

#include <algorithm>

TEST(TestLatch, OrderCheck) {
    size_t thread_num = 4;
    synchronize::Latch latch(thread_num);

    synchronize::Mutex m;
    std::vector<int> vector;

    std::vector<std::thread> ths;

    for (size_t i = 0; i < thread_num; ++i) {
        ths.emplace_back([&]() {
            for (size_t i = 0; i < 100000; ++i) {
                std::lock_guard<synchronize::Mutex> lk(m);
                vector.push_back(1);
            }
            latch.arrive_and_wait();
            for (size_t i = 0; i < 100000; ++i) {
                std::lock_guard<synchronize::Mutex> lk(m);
                vector.push_back(0);
            }
        });
    }
    for (auto& th : ths) {
        th.join();
    }
    size_t left_half_ones = std::count(vector.begin(), vector.begin() + vector.size() / 2, 1);
    ASSERT_EQ(thread_num * 100000, left_half_ones);
    size_t right_half_zeros = std::count(vector.begin() + vector.size() / 2, vector.end(), 0);
    ASSERT_EQ(thread_num * 100000, right_half_zeros);
}