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

set (BOOST_ENABLE_CMAKE ON)
FetchContent_Declare(
  Boost
  URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
  USES_TERMINAL_DOWNLOAD TRUE
  DOWNLOAD_NO_EXTRACT FALSE
)

FetchContent_MakeAvailable(boost)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fsanitize=address")

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

add_subdirectory(lock_free)
add_subdirectory(synchronize)
enable_testing ()

set(TESTS 
      test_mutex
      test_condition_variable
      test_shared_mutex
      test_latch
      test_semaphore
      test_barrier    
      test_threadpool_and_wg
      test_future
)

foreach (_test ${TESTS})

  add_executable(${_test} testing/${_test}.cpp)
  target_link_libraries(${_test} gtest_main gmock_main sync LockFree)
  add_test (NAME ${_test} COMMAND ${_test})

endforeach ()

add_executable(Sandbox sandbox.cpp)
target_link_libraries(Sandbox sync LockFree)

add_executable(EchoFiber fiber_echo.cpp)
target_include_directories(EchoFiber PRIVATE ${boost_SOURCE_DIR})
target_link_libraries(EchoFiber Boost::context Boost::asio sync)
