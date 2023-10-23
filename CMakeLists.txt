cmake_minimum_required(VERSION 3.26)
project(bignsort)

set(CMAKE_CXX_STANDARD 17)

add_executable(bignsort main.cpp
        sorting/sorting.h
        sorting/sorting.cpp)
