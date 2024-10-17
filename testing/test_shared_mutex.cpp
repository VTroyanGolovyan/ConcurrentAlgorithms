#include <gtest/gtest.h>
#include <thread>

#include "test_mutex.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
