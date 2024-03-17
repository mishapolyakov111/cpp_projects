#include "number.h"

uint32_t power(unsigned int a, unsigned int n) {
    unsigned int p = a;
    if (n == 0) {
        return 1;
    }
    for (int i = 0; i < n - 1; ++i) {
        p = p * a;
    }
    return p;
}

uint32_t countIntDigits(uint32_t i) {
    uint64_t countDigits = 0;
    while (i > 0) {
        countDigits++;
        i = i / 10;
    }
    return countDigits;
}

int endIdx(const uint2022_t &value) {
    int end = 0;
    for (int j = 0; j < 68; ++j) {
        if (value.signs[j] != 0) {
            end = j;
        }
    }
    return end;
}

uint2022_t billMultyply(const uint2022_t &value, uint32_t count) {
    uint2022_t result;

    for (int i = 0; i <= endIdx(value); ++i) {
        result.signs[i + count] = value.signs[i];
    }

    return result;
}

uint2022_t from_uint(uint32_t i) {
    uint2022_t a;

    a.signs[0] = i % 1000000000;
    a.signs[1] = i / 1000000000;

    return a;
}

uint2022_t from_string(const char *buff) {
    uint2022_t from_str_result;
    uint32_t number;

    int lenght = 0;
    while (buff[lenght] != '\0') {
        lenght += 1;
    }

    int i = lenght;
    while (i >= 1) {
        number = (buff[i - 1] - '0') * power(10, (lenght - i) % 9);
        from_str_result.signs[(lenght - i) / 9] += number;
        i--;
    }

    return from_str_result;
}

uint2022_t operator+(const uint2022_t &lhs, const uint2022_t &rhs) {
    uint2022_t add_result;
    uint64_t n = std::max(endIdx(lhs), endIdx(rhs));

    for (int i = 0; i <= n; ++i) {
        if (lhs.signs[i] + rhs.signs[i] < 1000000000) {
            add_result.signs[i] += lhs.signs[i] + rhs.signs[i];
        } else {
            add_result.signs[i] += (lhs.signs[i] + rhs.signs[i]) % 1000000000;
            add_result.signs[i + 1] = 1;
        }
    }

    return add_result;
}

uint2022_t operator-(const uint2022_t &lhs, const uint2022_t &rhs) {
    uint2022_t minus_result;
    uint2022_t lhs_copy = lhs;

    for (int i = 0; i <= endIdx(lhs_copy); ++i) {
        if (lhs_copy.signs[i] < rhs.signs[i]) {
            lhs_copy.signs[i + 1]--;
            minus_result.signs[i] = 1000000000 + lhs_copy.signs[i] - rhs.signs[i];
        } else {
            minus_result.signs[i] = lhs_copy.signs[i] - rhs.signs[i];
        }
    }

    return minus_result;
}

uint2022_t operator*(const uint2022_t &lhs, uint32_t i) {
    uint2022_t result;
    unsigned long long buff;

    uint32_t end = endIdx(lhs);
    for (int j = 0; j <= end; ++j) {
        buff = 1LL * lhs.signs[j] * i;

        result.signs[j] += buff % 1000000000;
        if (countIntDigits(result.signs[j]) > 9) {
            result.signs[j + 1]++;
            result.signs[j] = result.signs[j] % 1000000000;
        }

        result.signs[j + 1] += buff / 1000000000;
        if (countIntDigits(result.signs[j + 1]) > 9) {
            result.signs[j + 2]++;
            result.signs[j + 1] = result.signs[j] % 1000000000;
        }
    }

    return result;
}

uint2022_t operator*(const uint2022_t &lhs, const uint2022_t &rhs) {
    uint2022_t result;

    uint32_t endIdx_right = endIdx(rhs);
    for (int i = 0; i <= endIdx_right; ++i) {
        uint2022_t value = lhs * rhs.signs[i];
        result = billMultyply(value, i) + result;
    }

    return result;
}

uint2022_t operator/(const uint2022_t &lhs, const uint2022_t &rhs) {
    uint2022_t result;
    return result;
}

bool operator==(const uint2022_t &lhs, const uint2022_t &rhs) {
    if (endIdx(lhs) != endIdx(rhs)) {
        return false;
    }

    for (int i = 0; i <= endIdx(rhs); ++i) {
        if (lhs.signs[i] != rhs.signs[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const uint2022_t &lhs, const uint2022_t &rhs) {
    return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &stream, const uint2022_t &value) {
    int end = endIdx(value);
    stream << value.signs[end];

    for (int i = end - 1; i >= 0; --i) {
        uint32_t count = countIntDigits(value.signs[i]);
        if (count < 9) {
            for (int j = 0; j < 9 - count; ++j) {
                stream << '0';
            }
        }
        stream << value.signs[i];
    }

    return stream;
}
