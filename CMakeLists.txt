cmake_minimum_required(VERSION 3.21)
project(Algorithm_Exercises)

set(CMAKE_CXX_STANDARD 14)

add_executable(Sort basic/sort.cpp)
target_include_directories(Sort PUBLIC utils)
add_executable(BinaryPartition basic/binary_partition.cpp)
target_include_directories(BinaryPartition PUBLIC utils)
add_executable(TwoPointer basic/two_pointer.cpp)
add_executable(MergeIntervals basic/merge_intervals.cpp)
