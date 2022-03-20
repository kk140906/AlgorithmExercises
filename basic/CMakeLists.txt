cmake_minimum_required(VERSION 3.21)
project(Algorithm_Basic)
set(CMAKE_CXX_STANDARD 14)

add_executable(Sort ${CMAKE_CURRENT_SOURCE_DIR}/sort.cpp)
target_include_directories(Sort PUBLIC ${CMAKE_SOURCE_DIR}/utils)
add_executable(LRU ${CMAKE_CURRENT_SOURCE_DIR}/lru.cpp)
add_executable(MergeIntervals ${CMAKE_CURRENT_SOURCE_DIR}/merge_intervals.cpp)
add_executable(StaticStackArray ${CMAKE_CURRENT_SOURCE_DIR}/static_stack_array.cpp)
add_executable(StaticQueueArray ${CMAKE_CURRENT_SOURCE_DIR}/static_queue_array.cpp)
add_executable(StaticListArray ${CMAKE_CURRENT_SOURCE_DIR}/static_list_array.cpp)
add_executable(MonotonicStack ${CMAKE_CURRENT_SOURCE_DIR}/monotonic_stack.cpp)
add_executable(MonotonicQueue ${CMAKE_CURRENT_SOURCE_DIR}/monotonic_queue.cpp)

