cmake_minimum_required(VERSION 3.12)
project(algo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O2")

include_directories(include data)
add_subdirectory(test)
add_subdirectory(src)
