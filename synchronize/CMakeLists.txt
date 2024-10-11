cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Debug)

project(sync)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fsanitize=address")

set(SOURCE_FILES 
    Mutex.cpp
    SpinLock.cpp
    SharedMutex.cpp 
    SpinLock.cpp 
    Latch.cpp 
    CyclicBarrier.cpp 
)

add_library(Sync ${SOURCE_FILES})
