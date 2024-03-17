#include "lib/CircularBuffer.h"
#include <iostream>
#include <list>


int main() {
    std::allocator<char> allocator2;
    std::allocator<int> allocator1(allocator2);

    int* a = allocator1.allocate(10);


    std::cout << "hello\n";
    CircularBufferExt<char> buffer;
    buffer.push_front(')');
    buffer.push_front(':');

    for (auto& i: buffer) {
        std::cout << i;
    }

    return 0;
}