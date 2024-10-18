cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Debug)

project(Sync)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fsanitize=thread")

set(SOURCE_FILES 
    Mutex.cpp
    SpinLock.cpp
    SharedMutex.cpp 
    SpinLock.cpp 
    Latch.cpp 
    CyclicBarrier.cpp 
    ./wait_group/WaitGroup.cpp
    ./scheduler/ThreadPool.cpp
)

add_library(Sync ${SOURCE_FILES})
