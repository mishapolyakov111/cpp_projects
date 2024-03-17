#pragma once

#include <iostream>

namespace HelperFunction {
    template<typename Iterator, typename Predicate>
    bool is_palindrome(Iterator begin, Iterator end, Predicate predicate, std::input_iterator_tag) {
        typename Iterator::difference_type n = std::distance(begin, end);
        typename Iterator::difference_type i = n - 1;

        Iterator it = begin;
        Iterator begin_copy = begin;
        for (int j = 0; j < i; ++j) {
            ++it;
        }

        for (int j = 0; j < n / 2; ++j) {
            if (!predicate(*begin, *it)) {
                return false;
            }
            ++begin;
            --i;
            it = begin_copy;
            for (int k = 0; k < i; ++k) {
                ++it;
            }
        }
        return true;
    }

    template<typename Iterator, typename Predicate>
    bool is_palindrome(Iterator begin, Iterator end, Predicate predicate, std::bidirectional_iterator_tag) {
        typename Iterator::difference_type n = std::distance(begin, end);
        --end;
        for (int i = 0; i < n / 2; ++i) {
            if (!predicate(*begin, *end)) {
                return false;
            }
            ++begin;
            --end;
        }

        return true;
    }
}

namespace MyAlgorithm {
    template<typename InputIterator, typename Predicate>
    bool all_of(InputIterator begin, InputIterator end, Predicate predicate) {
        while (begin != end) {
            if (!predicate(*begin)) {
                return false;
            }
            ++begin;
        }

        return true;
    }

    template<typename InputIterator, typename Predicate>
    bool any_of(InputIterator begin, InputIterator end, Predicate predicate) {
        while (begin != end) {
            if (predicate(*begin)) {
                return true;
            }
            ++begin;
        }

        return false;
    }

    template<typename InputIterator, typename Predicate>
    bool none_of(InputIterator begin, InputIterator end, Predicate predicate) {
        while (begin != end) {
            if (predicate(*begin)) {
                return false;
            }
            ++begin;
        }

        return true;
    }

    template<typename InputIterator, typename Predicate>
    bool one_of(InputIterator begin, InputIterator end, Predicate predicate) {
        bool flag = false;

        while (begin != end) {
            if (predicate(*begin)) {
                if (flag) {
                    return false;
                }

                flag = true;
            }
            ++begin;
        }

        return flag;
    }

    template<typename InputIterator, typename Element_type>
    InputIterator find_not(InputIterator begin, InputIterator end, Element_type element) {
        while (begin != end) {
            if (*begin != element) {
                return begin;
            }
            ++begin;
        }

        return end;
    }

    template<typename InputIterator, typename Comparator>
    bool is_sorted(InputIterator begin, InputIterator end, Comparator comparator) {
        if (begin == end) {
            return true;
        }

        InputIterator it1 = begin;
        InputIterator it2 = ++begin;
        while (it2 != end) {
            if (!comparator(*it1, *it2)) {
                return false;
            }

            ++it1;
            ++it2;
        }

        return true;
    }

    template<typename InputIterator, typename Predicate>
    bool is_partitioned(InputIterator begin, InputIterator end, Predicate predicate) {
        if (std::distance(begin, end) < 2) {
            return true;
        }

        uint32_t cnt = 0;
        InputIterator it1 = begin;
        InputIterator it2 = ++begin;

        while (it2 != end) {
            if (predicate(*it1) != predicate(*it2)) {
                ++cnt;
            }
            if (cnt > 1) {
                return false;
            }

            ++it1;
            ++it2;
        }

        return cnt == 1;
    }

    template<typename InputIterator, typename Element_type>
    InputIterator find_backward(InputIterator begin, InputIterator end, Element_type element) {
        InputIterator it = end;
        while (begin != end) {
            if (*begin == element) {
                it = begin;
            }
            ++begin;
        }
        return it;
    }

    template<typename Iterator, typename Predicate>
    bool is_palindrome(Iterator begin, Iterator end, Predicate predicate) {
        if (begin == end) {
            return true;
        }

        typename std::iterator_traits<Iterator>::iterator_category category;
        return HelperFunction::is_palindrome(begin, end, predicate, category);
    }

    template<typename Iterator>
    bool is_palindrome(Iterator begin, Iterator end) {
        if (begin == end) {
            return true;
        }

        typename std::iterator_traits<Iterator>::iterator_category category;
        return HelperFunction::is_palindrome(begin, end, std::equal_to<>(), category);
    }
}