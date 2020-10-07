cmake_minimum_required(VERSION 3.15)
project(Malloc_Replacement)

set(CMAKE_CXX_STANDARD 17)

add_executable(Malloc_Replacement main.cpp Hash.cpp Hash.h)