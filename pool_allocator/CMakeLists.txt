cmake_minimum_required(VERSION 3.23)
project(labwork_9_mishapolyakov111)

set(CMAKE_CXX_STANDARD 14)

add_executable(labwork_9_mishapolyakov111
        main.cpp
        PoolAllocator/PollAllocator.h
        PoolAllocator/Pool.h)
