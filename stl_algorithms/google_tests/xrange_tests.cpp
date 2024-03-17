#include "xrange.h"
#include "gtest/gtest.h"

TEST(XRANGE_TESTS, TEST_1) {
    std::vector<int> vec;
    for (auto x: xrange(6)) {
        vec.push_back(x);
    }

    std::vector<int> check = {0, 1, 2, 3, 4, 5};
    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), check.begin(), check.end()));
}

TEST(XRANGE_TESTS, TEST_2) {
    std::vector<int> vec;
    for (auto x: xrange(-6)) {
        vec.push_back(x);
    }

    std::vector<int> check = {0, -1, -2, -3, -4, -5};
    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), check.begin(), check.end()));
}

TEST(XRANGE_TESTS, TEST_3) {
    std::vector<double> vec;
    for (auto x: xrange(-6.0, 10.5)) {
        vec.push_back(x);
    }

    std::vector<double> check = {-6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), check.begin(), check.end()));
}

TEST(XRANGE_TESTS, TEST_4) {
    std::vector<double> vec;
    for (auto x: xrange(10.5, -6.5)) {
        vec.push_back(x);
    }

    std::vector<double> check = {10.5, 9.5, 8.5, 7.5, 6.5, 5.5, 4.5, 3.5, 2.5, 1.5, 0.5, -0.5, -1.5, -2.5, -3.5, -4.5, -5.5};
    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), check.begin(), check.end()));
}

TEST(XRANGE_TESTS, TEST_5) {
    std::vector<int> vec;
    for (auto x: xrange(1, 7, 2)) {
        vec.push_back(x);
    }

    std::vector<int> check = {1, 3, 5};
    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), check.begin(), check.end()));
}

TEST(XRANGE_TESTS, TEST_6) {
    std::vector<int> vec;
    for (auto x: xrange(7, 1, -2)) {
        vec.push_back(x);
    }

    std::vector<int> check = {7, 5, 3};
    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), check.begin(), check.end()));
}

TEST(XRANGE_TESTS, EMPY_TEST) {
    std::vector<int> vec;
    for (auto x: xrange(1, 1)) {
        vec.push_back(x);
    }

    ASSERT_TRUE(vec.empty());
}