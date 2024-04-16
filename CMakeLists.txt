cmake_minimum_required(VERSION 3.27)
project(coordinate-transformations)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx2 -mfma -O3")

add_executable(test test.cpp rotate.cpp translate.cpp transform.cpp)
