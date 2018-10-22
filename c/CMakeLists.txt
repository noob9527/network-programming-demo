cmake_minimum_required(VERSION 3.5)
project(network_programming-demo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_CXX_FLAGS -pthread)

#include_directories(include)
#link_directories(lib)

add_subdirectory(src)
