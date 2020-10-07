cmake_minimum_required(VERSION 3.15)
project(Parser)

set(CMAKE_CXX_STANDARD 17)

add_executable(Parser main.cpp cont.cpp cont.hpp env.cpp env.hpp expr.cpp expr.hpp parse.cpp parse.hpp pointer.h step.cpp step.hpp value.cpp value.hpp MSDScriptLib.h)
add_library(MSDLib cont.cpp env.cpp expr.cpp parse.cpp step.cpp value.cpp)