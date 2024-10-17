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
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fsanitize=thread")

add_compile_options(-fsanitize=thread)
add_link_options(-fsanitize=thread)

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
)

foreach (_test ${TESTS})

add_executable(${_test} testing/${_test}.cpp)
target_link_libraries(${_test} gtest_main gmock_main Sync LockFree)
add_test (NAME ${_test} COMMAND ${_test})

endforeach ()
