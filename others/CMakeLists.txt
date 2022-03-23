cmake_minimum_required(VERSION 3.21)
project(Algorithm_Others)
set(CMAKE_CXX_STANDARD 14)

add_executable(LRU ${CMAKE_CURRENT_SOURCE_DIR}/lru.cpp)
add_executable(MergeIntervals ${CMAKE_CURRENT_SOURCE_DIR}/merge_intervals.cpp)

