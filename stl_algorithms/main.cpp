#include <iostream>
#include <vector>
#include <algorithm>
#include <forward_list>
#include <MyAlgorithms.h>
#include "xrange.h"
#include "zip.h"

class myClass {
public:
    myClass operator++() {
        a += 2;
        return *this;
    }

    myClass operator--() {
        a -= 2;
        return *this;
    }

    myClass operator+=(const myClass& other) {
        a *= other.a;
        return *this;
    }


    bool operator<(const myClass& other) const {
        return a < other.a;
    }

    bool operator<=(const myClass& other) const {
        return a <= other.a;
    }

    bool operator>(const myClass& other) const {
        return a > other.a;
    }

    bool operator==(const myClass& other) const {
        return a == other.a;
    }

    myClass() = default;

    explicit myClass(int b) {
        a = b;
    }

public:
    int a = 1;
};

int main() {
    std::forward_list<int> list  ={1, 2, 4, 5};

    std::cout << std::distance(list.end(), list.begin());
    return 0;
}
