cmake_minimum_required(VERSION 3.23)

project(LruCache)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# add_executable(LruCache)

# target_sources(LruCache
#   PRIVATE
#     lru_main.cc
# )

# target_compile_options(LruCache
#   PRIVATE
#     -g
#     -Wall
#     -Wextra
# )

Include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(lfu_test lfu_test.cpp)
target_link_libraries(lfu_test
    PRIVATE
        GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(lfu_test)