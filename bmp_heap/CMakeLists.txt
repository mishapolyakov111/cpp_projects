cmake_minimum_required(VERSION 3.23)
project(labwork_3_mishapolyakov111)
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(labwork_3_mishapolyakov111
        bin/main.cpp
        lib/bitmap.cpp
        lib/parcing.cpp
        )

set(CMAKE_CXX_STANDARD 20)

include_directories(lib)
include_directories(bin)

