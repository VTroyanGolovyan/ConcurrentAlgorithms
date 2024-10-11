cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Debug)

project(concurrency)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2 
)
FetchContent_MakeAvailable(googletest)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fsanitize=address")
add_subdirectory(lock_free)
add_subdirectory(synchronize)

add_executable(TESTS testing/tests.cpp)
target_link_libraries(TESTS gtest_main gmock_main Sync LockFree)
