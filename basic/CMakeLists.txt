cmake_minimum_required(VERSION 3.21)
project(Algorithm_Basic)
set(CMAKE_CXX_STANDARD 14)

add_executable(Sort ${CMAKE_CURRENT_SOURCE_DIR}/sort.cpp)
target_include_directories(Sort PUBLIC ${CMAKE_SOURCE_DIR}/utils)



