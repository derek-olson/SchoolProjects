cmake_minimum_required(VERSION 3.15)
project(ThreadSafeQueue)

set(CMAKE_CXX_STANDARD 17)

add_executable(ThreadSafeQueue SerialQueue.hpp SerialQueueTests.cpp SerialQueueTests.h )

add_executable(ConcurrentQueue ConcurrentQueue.h concurrentQueueTests.cpp)