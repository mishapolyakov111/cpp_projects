#include "gtest/gtest.h"
#include "zip.h"

TEST(ZIP_TEST, TEST_1) {
    std::vector<int> v = {2, 3, 9};
    std::initializer_list<char> l = {'*', '#', '9', '\\'};

    std::vector<std::pair<int, char>> vec;
    std::vector<std::pair<int, char>> check = {{2, '*'}, {3, '#'}, {9, '9'}};
    for(auto it: zip(v, l)){
        vec.push_back(it);
    }

    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), check.begin(), check.end()));
}

TEST(ZIP_TEST, TEST_2) {
    std::vector<int> v;
    std::initializer_list<char> l = {'*', '#', '9', '\\'};

    std::vector<std::pair<int, char>> vec;
    std::vector<std::pair<int, char>> check = {{2, '*'}, {3, '#'}, {9, '9'}};
    for(auto it: zip(v, l)){
        vec.push_back(it);
    }

    ASSERT_TRUE(vec.empty());
}