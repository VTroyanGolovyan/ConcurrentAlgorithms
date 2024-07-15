cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Debug)

project(lock_free)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fsanitize=address")

set(SOURCE_FILES 
    backoff/EmptyBackoff.cpp
    backoff/ExponentialBackoff.cpp
    memory/hazard/HazardPtr.cpp
)

add_library(LockFree ${SOURCE_FILES})
