cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Debug)

project(sync)

include(FetchContent)

set (BOOST_ENABLE_CMAKE ON)

FetchContent_Declare(
  Boost
  URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
  USES_TERMINAL_DOWNLOAD TRUE
  DOWNLOAD_NO_EXTRACT FALSE
)

FetchContent_MakeAvailable(boost)

message(${boost_SOURCE_DIR})

set(SOURCE_FILES 
    Mutex.cpp
    SpinLock.cpp
    SharedMutex.cpp 
    SpinLock.cpp 
    Latch.cpp 
    CyclicBarrier.cpp 
    ./wait_group/WaitGroup.cpp
    ./scheduler/ThreadPool.cpp
    ./coro/Coroutine.cpp
    ./fiber/Fiber.cpp
    ./fiber/io/io.cpp
)

add_library(sync ${SOURCE_FILES})
target_include_directories(
    sync PUBLIC 
    ${boost_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
)
target_link_libraries(sync Boost::context Boost::asio)