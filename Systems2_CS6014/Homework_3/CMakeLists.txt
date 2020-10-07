cmake_minimum_required(VERSION 3.15)
project(Homework_3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
set(CMAKE_EXE_LINKER_FLAGS -fsanitize=address)
add_executable(Homework_3 main.cpp Key.cpp Key.h Tables.cpp Tables.h rc4.cpp rc4.h)