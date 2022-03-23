cmake_minimum_required(VERSION 3.21)
project(Algorithm_String)
set(CMAKE_CXX_STANDARD 14)


add_executable(KMP ${CMAKE_CURRENT_SOURCE_DIR}/kmp.cpp)
add_executable(StringHash ${CMAKE_CURRENT_SOURCE_DIR}/string_hash.cpp)

