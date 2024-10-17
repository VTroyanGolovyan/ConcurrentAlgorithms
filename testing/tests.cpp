#include <gtest/gtest.h>
#include <thread>

#include "test_mutex.hpp"
#include "test_condition_variable.hpp"
#include "test_shared_mutex.hpp"
#include "test_semaphore.hpp"
#include "test_latch.hpp"
#include "test_barrier.hpp"

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}