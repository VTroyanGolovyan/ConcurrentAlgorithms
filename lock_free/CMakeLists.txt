cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Debug)

project(lock_free)

set(SOURCE_FILES 
    ./backoff/EmptyBackoff.cpp
    ./backoff/ExponentialBackoff.cpp
    ./memory/hazard/HazardPtr.cpp
)

add_library(LockFree ${SOURCE_FILES})
