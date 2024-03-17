
#include <lib/number.h>
#include <iostream>

int main() {
    uint2022_t value = from_string("3");
    uint2022_t value1 = from_string("3");

    uint2022_t misha = value * value1;
    std::cout << misha;
    return 0;
}
