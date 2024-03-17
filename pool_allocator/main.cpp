#include <iostream>
#include <vector>
#include <chrono>
#include "PoolAllocator/PollAllocator.h"

int main() {

    PoolAllocator<float> allocator1 = PoolAllocator<float>{{2, 20000000}};

    std::vector<int, PoolAllocator<int>> vector1(allocator1);
    std::vector<int, std::allocator<int>> vector2(std::allocator<int>());

    vector1 = vector2;









    return 0;
}
