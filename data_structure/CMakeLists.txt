cmake_minimum_required(VERSION 3.21)
project(Algorithm_Data_Structure)
set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/utils)

add_executable(StaticStackArray ${CMAKE_CURRENT_SOURCE_DIR}/static_stack_array.cpp)
add_executable(StaticQueueArray ${CMAKE_CURRENT_SOURCE_DIR}/static_queue_array.cpp)
add_executable(StaticListArray ${CMAKE_CURRENT_SOURCE_DIR}/static_list_array.cpp)
add_executable(MonotonicStack ${CMAKE_CURRENT_SOURCE_DIR}/monotonic_stack.cpp)
add_executable(MonotonicQueue ${CMAKE_CURRENT_SOURCE_DIR}/monotonic_queue.cpp)
add_executable(Hash ${CMAKE_CURRENT_SOURCE_DIR}/hash.cpp)
add_executable(UnionFind ${CMAKE_CURRENT_SOURCE_DIR}/union_find.cpp)

