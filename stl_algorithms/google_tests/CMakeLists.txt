project(google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(tests algorithms_tests.cpp xrange_tests.cpp zip_tests.cpp)

target_link_libraries(tests gtest gtest_main)