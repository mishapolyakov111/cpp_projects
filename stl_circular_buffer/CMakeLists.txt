cmake_minimum_required(VERSION 3.23)
project(labwork8-mishapolyakov111)

set(CMAKE_CXX_STANDARD 17)

add_executable(labwork-8-mishapolyakov111 main.cpp lib/CircularBuffer.h lib/CircularBufferExt.h)

add_subdirectory(Google_tests)