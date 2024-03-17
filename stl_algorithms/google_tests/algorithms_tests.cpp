#include <forward_list>

#include "MyAlgorithms.h"
#include "gtest/gtest.h"

template <typename value_type>
bool EvenNumber(value_type a){
        return a % 2 == 0;
}

template <typename value_type>
bool Equal_3(value_type a){
    return a == 3;
}

template <typename T>
bool mod_11(T a, T b) {
    return a % 11 == b % 11;
}

TEST(ALGORITHM_TEST, ALL_OF_1) {
    std::forward_list<int> list = {0, 2, 4, 6, 8, 10};
    ASSERT_TRUE(MyAlgorithm::all_of(list.begin(), list.end(), EvenNumber<int>));
}

TEST(ALGORITHM_TEST, ALL_OF_2) {
    std::forward_list<int> list = {0, 1, 4, 6, 8, 10};
    ASSERT_FALSE(MyAlgorithm::all_of(list.begin(), list.end(), EvenNumber<int>));
}

TEST(ALGORITHM_TEST, ALL_OF_3) {
    std::forward_list<int> list = {0, 1, 4, 6, 8, 10};
    ASSERT_TRUE(MyAlgorithm::all_of(list.begin(), list.begin(), EvenNumber<int>));
}

TEST(ALGORITHM_TEST, ANY_OF_1) {
    std::forward_list<int> list = {0, 1, 3, 5, 7, 9};
    ASSERT_TRUE(MyAlgorithm::any_of(list.begin(), list.end(), EvenNumber<int>));
}

TEST(ALGORITHM_TEST, ANY_OF_2) {
    std::forward_list<int> list = {1, 1, 3, 5, 7, 9};
    ASSERT_FALSE(MyAlgorithm::any_of(list.begin(), list.end(), EvenNumber<int>));
}

TEST(ALGORITHM_TEST, NONE_OF_1) {
    std::forward_list<int> list = {1, 1, 3, 5, 7, 9};
    ASSERT_TRUE(MyAlgorithm::none_of(list.begin(), list.end(), EvenNumber<int>));
}

TEST(ALGORITHM_TEST, NONE_OF_2) {
    std::forward_list<int> list;
    ASSERT_TRUE(MyAlgorithm::none_of(list.begin(), list.end(), EvenNumber<int>));
}

TEST(ALGORITHM_TEST, NONE_OF_3) {
    std::forward_list<int> list = {1, 1, 3, 5, 7, 0};
    ASSERT_FALSE(MyAlgorithm::none_of(list.begin(), list.end(), EvenNumber<int>));
}

TEST(ALGORITHM_TEST, ONE_OF_1) {
    std::forward_list<int> list = {1, 1, 3, 5, 7, 0};
    ASSERT_TRUE(MyAlgorithm::one_of(list.begin(), list.end(), Equal_3<int>));
}

TEST(ALGORITHM_TEST, ONE_OF_2) {
    std::forward_list<int> list = {1};
    ASSERT_FALSE(MyAlgorithm::one_of(list.begin(), list.end(), Equal_3<int>));
}

TEST(ALGORITHM_TEST, ONE_OF_3) {
    std::forward_list<int> list = {8, 3, 3, 1, 5};
    ASSERT_FALSE(MyAlgorithm::one_of(list.begin(), list.end(), Equal_3<int>));
}

TEST(ALGORITHM_TEST, FIND_NOT_1) {
    std::forward_list<int> list(10, 3);
    auto it = MyAlgorithm::find_not(list.begin(), list.end(), 3);
    ASSERT_EQ(it, list.end());
}

TEST(ALGORITHM_TEST, FIND_NOT_2) {
    std::forward_list<int> list = {1, 1, 1, 1, 5, 6, 1, 7};
    auto it = MyAlgorithm::find_not(list.begin(), list.end(), 1);
    ASSERT_EQ(*it, 5);
    ASSERT_EQ(*(++it), 6);
}

TEST(ALGORITHM_TEST, IS_SORTED_1) {
    std::forward_list<int> list = {7, 6, 5, 5, 4, 1};
    ASSERT_TRUE(MyAlgorithm::is_sorted(list.begin(), list.end(), std::greater_equal()));
}

TEST(ALGORITHM_TEST, IS_SORTED_2) {
    std::forward_list<int> list = {5, 6, 5, 5, 4, 1};
    ASSERT_FALSE(MyAlgorithm::is_sorted(list.begin(), list.end(), std::greater_equal()));
}

TEST(ALGORITHM_TEST, IS_SORTED_3) {
    std::forward_list<int> list;
    ASSERT_TRUE(MyAlgorithm::is_sorted(list.begin(), list.end(), std::greater_equal()));
}

TEST(ALGORITHM_TEST, IS_PARTITIONED_1) {
    std::forward_list<int> list = {1, 3, 5, 6, 6, 6};
    ASSERT_TRUE(MyAlgorithm::is_partitioned(list.begin(), list.end(), EvenNumber<int>));
}

TEST(ALGORITHM_TEST, IS_PARTITIONED_2) {
    std::forward_list<int> list = {1, 3, 5, 6, 6, 1};
    ASSERT_FALSE(MyAlgorithm::is_partitioned(list.begin(), list.end(), EvenNumber<int>));
}

TEST(ALGORITHM_TEST, IS_PARTITIONED_3) {
    std::forward_list<int> list = {1, 3, 5};
    ASSERT_FALSE(MyAlgorithm::is_partitioned(list.begin(), list.end(), EvenNumber<int>));
}

TEST(ALGORITHM_TEST, IS_PARTITIONED_4) {
    std::forward_list<int> list = {2, 6, 6 ,6, 6, 88, 100};
    ASSERT_FALSE(MyAlgorithm::is_partitioned(list.begin(), list.end(), EvenNumber<int>));
}

TEST(ALGORITHM_TEST, IS_PARTITIONED_5) {
    std::forward_list<int> list;
    ASSERT_TRUE(MyAlgorithm::is_partitioned(list.begin(), list.end(), EvenNumber<int>));
}

TEST(ALGORITHM_TEST, FIND_BACKWARD_1) {
    std::forward_list<int> list = {1, 2, 9, 0, 88, 77, 1, 543};
    auto it = MyAlgorithm::find_backward(list.begin(), list.end(), 1);
    ASSERT_EQ(*it, 1);
    ASSERT_EQ(*(++it), 543);
}

TEST(ALGORITHM_TEST, FIND_BACKWARD_2) {
    std::forward_list<int> list = {1, 2, 9, 4, 88, 77, 1, 543};
    auto it = MyAlgorithm::find_backward(list.begin(), list.end(), 0);
    ASSERT_EQ(it, list.end());
}

TEST(ALGORITHM_TEST, IS_PALINDROME_1) {
    std::forward_list<int> list = {1, 3, 3, 5, 1};
    ASSERT_FALSE(MyAlgorithm::is_palindrome(list.begin(), list.end()));
}

TEST(ALGORITHM_TEST, IS_PALINDROME_2) {
    std::forward_list<int> list = {1, 5, 3, 5, 1};
    ASSERT_TRUE(MyAlgorithm::is_palindrome(list.begin(), list.end()));
}

TEST(ALGORITHM_TEST, IS_PALINDROME_3) {
    std::forward_list<int> list;
    ASSERT_TRUE(MyAlgorithm::is_palindrome(list.begin(), list.end()));
}

TEST(ALGORITHM_TEST, IS_PALINDROME_4) {
    std::forward_list<int> list = {1};
    ASSERT_TRUE(MyAlgorithm::is_palindrome(list.begin(), list.end()));
}

TEST(ALGORITHM_TEST, IS_PALINDROME_5) {
    std::forward_list<int> list = {1, 13, 2, 2, 23};
    ASSERT_TRUE(MyAlgorithm::is_palindrome(list.begin(), list.end(), mod_11<int>));
}

TEST(ALGORITHM_TEST, IS_PALINDROME_6) {
    std::vector<int> list = {1, 13, 2, 2, 23};
    ASSERT_TRUE(MyAlgorithm::is_palindrome(list.begin(), list.end(), mod_11<int>));
}