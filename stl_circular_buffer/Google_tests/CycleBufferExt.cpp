#include "gtest/gtest.h"
#include "../lib/CircularBufferExt.h"

TEST(CIRCULAR_BUFFER_EXT_TEST, CONSTRUCTOR_TEST) {
    CircularBufferExt<int> buffer1;
    ASSERT_EQ(buffer1.empty(), true);
    ASSERT_TRUE(buffer1.begin() == buffer1.end());
    ASSERT_EQ(buffer1.max_size(), 1);

    CircularBufferExt<int> buffer2(10);
    ASSERT_EQ(buffer2.empty(), true);
    ASSERT_EQ(buffer2.max_size(), 10);

    CircularBufferExt<int> buffer3(5, 1);
    std::vector check = {1, 1, 1, 1, 1};

    ASSERT_EQ(buffer3.empty(), false);
    ASSERT_EQ(buffer3.max_size(), 5);
    ASSERT_EQ(buffer3.size(), 5);
    ASSERT_EQ(std::equal(buffer3.begin(), buffer3.end(), check.begin()), true);

    check = {1, 2, 3, 4, 5, 6, 7};
    CircularBufferExt<int> buffer4(check.begin(), check.end());
    ASSERT_EQ(buffer4.empty(), false);
    ASSERT_EQ(buffer4.max_size(), 7);
    ASSERT_EQ(buffer4.size(), 7);
    ASSERT_EQ(std::equal(buffer4.begin(), buffer4.end(), check.begin()), true);

    check = {};
    CircularBufferExt<int> buffer5(check.begin(), check.end());
    ASSERT_EQ(buffer5.empty(), true);
    ASSERT_EQ(buffer5.max_size(), 0);
    ASSERT_EQ(buffer5.size(), 0);
    ASSERT_EQ(std::equal(buffer5.begin(), buffer5.end(), check.begin()), true);
}

TEST(CIRCULAR_BUFFER_EXT_TEST, OPERATOR_TEST) {
    CircularBufferExt<int> buffer1;
    CircularBufferExt<int> buffer2(5, 1);
    buffer2 = buffer1;
    ASSERT_EQ(std::equal(buffer1.begin(), buffer1.end(), buffer2.begin(), buffer2.end()), true);

    buffer1.push_back(2);
    ASSERT_FALSE(buffer1.begin() == buffer2.begin());

    ASSERT_FALSE(buffer1 == buffer2);
    ASSERT_TRUE(buffer1 != buffer2);
}

TEST(CIRCULAR_BUFFER_EXT_TEST, ALGORITHMS_TEST) {
    CircularBufferExt<int> buffer; //empty buffer
    std::sort(buffer.begin(), buffer.end());
    ASSERT_TRUE(buffer.empty() and buffer.max_size() == 1);

    std::vector<int> check = {1};
    buffer.push_back(1);
    std::sort(buffer.begin(), buffer.end());
    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), check.begin()));

    std::reverse(buffer.begin(), buffer.end());
    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), check.begin()));

    buffer = {1, 6, 1, 7, 0, -1, -199};
    check = {-199, -1, 0, 1, 1, 6, 7};
    std::sort(buffer.begin(), buffer.end());
    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), check.begin()));

    std::reverse(buffer.begin(), buffer.end());
    check = {7, 6, 1, 1, 0, -1, -199};
    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), check.begin()));
}

TEST(CIRCULAR_BUFFER_EXT_TEST, SWAP_TEST) {
    std::vector check = {1, 6, 1, 7, 0, -1, -199};

    CircularBufferExt<int> buffer;
    CircularBufferExt<int> buffer1 = {1, 6, 1, 7, 0, -1, -199};

    buffer.swap(buffer1);

    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), check.begin()));
    ASSERT_EQ(buffer1.size(), 0);
}

TEST(CIRCULAR_BUFFER_EXT_TEST, INSERT_TEST) {
    CircularBufferExt<int> buffer1 = {1, 6, 1, 7, 0, -1, -199}; ////full

    CircularBufferExt<int> buffer2(10); ////empty

    CircularBufferExt<int> buffer3 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    buffer3.pop_front();
    buffer3.pop_front();
    buffer3.push_back(10);
    ////buffer3: (end, empty_cell, begin->2, 3, 4, 5, 6, 7, 8, 9, 10)

    CircularBufferExt<int> buffer4; ////empty default

    CircularBufferExt<int>::iterator it = buffer2.insert(buffer2.cbegin(), buffer1.cbegin() + 1, buffer1.cend() - 1);
    std::vector<int> check = {6, 1, 7, 0, -1};
    ASSERT_TRUE(std::equal(buffer2.begin(), buffer2.end(), check.begin(), check.end()));
    ASSERT_TRUE(buffer2.begin() == it);

    buffer1.insert(buffer1.cend(), 1);
    check = {1, 6, 1, 7, 0, -1, -199, 1};
    ASSERT_TRUE(std::equal(buffer1.begin(), buffer1.end(), check.begin(), check.end()));

    buffer3.insert(buffer3.cbegin() + 2, {1, 2, 3});
    check = {2, 3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_TRUE(std::equal(buffer3.begin(), buffer3.end(), check.begin(), check.end()));

    buffer3.insert(buffer3.cbegin() + 2, 239);
    check = {2, 3, 239, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_TRUE(std::equal(buffer3.begin(), buffer3.end(), check.begin(), check.end()));
}

TEST(CIRCULAR_BUFFER_EXT_TEST, ERASE_TEST) {
    CircularBufferExt<int> buffer1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    buffer1.pop_front();
    buffer1.pop_front();
    buffer1.push_back(10);
    buffer1.push_back(11);
    ////buffer1: (11, end, begin->2, 3, 4, 5, 6, 7, 8, 9, 10)

    buffer1.erase(buffer1.cbegin());
    std::vector<int> check = {3, 4, 5, 6, 7, 8, 9, 10, 11};
    ASSERT_TRUE(std::equal(buffer1.begin(), buffer1.end(), check.begin(), check.end()));

    buffer1.erase(buffer1.cend()); // nothing to change
    ASSERT_TRUE(std::equal(buffer1.begin(), buffer1.end(), check.begin(), check.end()));

    buffer1.erase(buffer1.cbegin() + 1, buffer1.cend() - 1);
    check = {3, 11};
    ASSERT_TRUE(std::equal(buffer1.begin(), buffer1.end(), check.begin(), check.end()));

    buffer1.erase(buffer1.cbegin(), buffer1.cend());
    ASSERT_TRUE(buffer1.empty());
}

TEST(CIRCULAR_BUFFER_EXT_TEST, ASSIGN_TEST) {
    std::vector<int> check = {3, 4, 5, 6, 7, 8, 9, 10, 11};
    CircularBufferExt<int> buffer1;
    CircularBufferExt<int> buffer2(10);
    CircularBufferExt<int> buffer3 = {9, 8, 7, 6, 5, 4, 3, 2};

    buffer1.assign(check.begin(), check.begin() + 1);
    ASSERT_TRUE(std::equal(buffer1.begin(), buffer1.end(), check.begin(), check.begin() + 1));

    buffer1.assign({3, 4, 5, 6, 7, 8, 9, 10, 11});
    ASSERT_TRUE(std::equal(buffer1.begin(), buffer1.end(), check.begin(), check.end()));

    buffer2.assign(check.cbegin(), check.cend());
    ASSERT_TRUE(std::equal(buffer2.begin(), buffer2.end(), check.begin(), check.end()));

    buffer3.assign(2, 3);
    check = {3, 3};
    ASSERT_TRUE(std::equal(buffer3.begin(), buffer3.end(), check.begin(), check.end()));
}

TEST(CIRCULAR_BUFFER_EXT_TEST, PUSH_BACK_TEST) {
    CircularBufferExt<int> buffer1;
    buffer1.push_back(1);
    buffer1.push_back(1);
    buffer1.push_back(1);

    std::vector<int> check = {1, 1, 1};
    ASSERT_TRUE(std::equal(buffer1.begin(), buffer1.end(), check.begin(), check.end()));

    CircularBufferExt<int> buffer2(10);

    for (int i = 0; i < 5; ++i) {
        buffer2.push_back(i + 1);
    }

    check = {1, 2, 3, 4, 5};
    ASSERT_TRUE(std::equal(buffer2.begin(), buffer2.end(), check.begin(), check.end()));
}

TEST(CIRCULAR_BUFFER_EXT_TEST, PUSH_FRONT_TEST) {
    CircularBufferExt<int> buffer1;
    buffer1.push_front(1);
    buffer1.push_front(1);
    buffer1.push_front(1);

    std::vector<int> check = {1, 1, 1};
    ASSERT_TRUE(std::equal(buffer1.begin(), buffer1.end(), check.begin(), check.end()));

    CircularBufferExt<int> buffer2(10);

    for (int i = 0; i < 5; ++i) {
        buffer2.push_front(i + 1);
    }

    check = {5, 4, 3, 2, 1};
    ASSERT_TRUE(std::equal(buffer2.begin(), buffer2.end(), check.begin(), check.end()));
}

TEST(CIRCULAR_BUFFER_EXT_TEST, POP_BACK_TEST) {
    CircularBufferExt<int> buffer1;
    buffer1.push_back(1);
    buffer1.pop_back();
    buffer1.pop_back();
    buffer1.pop_back();
    ASSERT_TRUE(buffer1.empty());

    CircularBufferExt<int> buffer2(10);

    for (int i = 0; i < 5; ++i) {
        buffer2.push_back(i + 1);
    }
    buffer2.pop_back();
    buffer2.pop_back();

    std::vector<int> check = {1, 2, 3};
    ASSERT_TRUE(std::equal(buffer2.begin(), buffer2.end(), check.begin(), check.end()));
}

TEST(CIRCULAR_BUFFER_EXT_TEST, POP_FRONT_TEST) {
    CircularBufferExt<int> buffer1;
    buffer1.push_back(1);
    buffer1.pop_front();
    buffer1.pop_front();
    buffer1.pop_front();
    ASSERT_TRUE(buffer1.empty());

    CircularBufferExt<int> buffer2(10);

    for (int i = 0; i < 5; ++i) {
        buffer2.push_back(i + 1);
    }
    buffer2.pop_front();
    buffer2.pop_front();

    std::vector<int> check = {3, 4, 5};
    ASSERT_TRUE(std::equal(buffer2.begin(), buffer2.end(), check.begin(), check.end()));
}