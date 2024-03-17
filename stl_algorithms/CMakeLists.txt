cmake_minimum_required(VERSION 3.23)
project(labwork_11_mishapolyakov111)

set(CMAKE_C_STANDARD 17)

include_directories(.)
include_directories(lib)

add_executable(labwork_11_mishapolyakov111
        lib/MyAlgorithms.h
        lib/xrange.h
        lib/zip.h
        main.cpp)

add_subdirectory(google_tests)
