#include "../synchronize/CyclicBarrier.hpp"

#include <algorithm>

TEST(TestBarrier, OrderCheck) {
    size_t thread_num = 4;
    size_t wave_cnt = 1000;
    size_t th_pushes = 1000;

    synchronize::CyclicBarrier barrier(thread_num);

    synchronize::Mutex m;
    std::vector<int> vector;

    std::vector<std::thread> ths;

    for (size_t i = 0; i < thread_num; ++i) {
        ths.emplace_back([&]() {
            for (size_t vawe = 0; vawe < wave_cnt; ++vawe) {
                for (size_t i = 0; i < th_pushes; ++i) {
                    std::lock_guard<synchronize::Mutex> lk(m);
                    vector.push_back(1);
                }
                barrier.arrive_and_wait();
                for (size_t i = 0; i < th_pushes; ++i) {
                    std::lock_guard<synchronize::Mutex> lk(m);
                    vector.push_back(0);
                }
                barrier.arrive_and_wait();
            }
            
        });
    }
    for (auto& th : ths) {
        th.join();
    }
    size_t batch = thread_num * th_pushes;
    for (size_t vawe = 0; vawe < wave_cnt; ++vawe) {
        size_t left_half_ones = std::count(vector.begin() + vawe * (2 * batch), vector.begin() + vawe * 2 * batch + batch, 1);
        ASSERT_EQ(batch, left_half_ones);
        size_t right_half_zeros = std::count(vector.begin() + vawe * 2 * batch + batch, vector.begin() + vawe * 2 * batch + 2 * batch, 0);
        ASSERT_EQ(batch, right_half_zeros);
    } 
    
}