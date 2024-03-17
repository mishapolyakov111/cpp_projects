#pragma once

#include <iostream>

template<typename Container_type1, typename Container_type2>
class zip {
public:
    class zipIterator {
    public:
        typedef typename Container_type1::iterator first_iterator_type;
        typedef typename Container_type2::iterator second_iterator_type;

        typedef std::pair<first_iterator_type, second_iterator_type> iterator_pair_type;
        typedef std::pair<typename Container_type1::value_type, typename Container_type2::value_type> value_type;

        typedef typename std::input_iterator_tag iterator_category;
        typedef ptrdiff_t difference_type;
        typedef value_type* pointer;
        typedef value_type& reference;

        zipIterator(first_iterator_type first, second_iterator_type second) : pair_({first, second}) {}

        zipIterator() : pair_(iterator_pair_type{}) {}

        zipIterator& operator++() {
            ++pair_.first;
            ++pair_.second;
            return *this;
        }

        zipIterator operator++(int) {
            first_iterator_type first_copy = pair_.first;
            second_iterator_type second_copy = pair_.second;
            ++(*this);
            return zipIterator(first_copy, second_copy);
        }

        value_type operator*() const {
            value_type pair{*(pair_.first), *(pair_.second)};
            return pair;
        }

        bool operator==(const zipIterator& iterator) {
            return pair_ == iterator.pair_;
        }

        bool operator!=(const zipIterator& iterator) {
            return pair_ != iterator.pair_;
        }

    private:
        iterator_pair_type pair_;
    };

public:
    typedef zipIterator iterator;

    zip(Container_type1& first, Container_type2& second) {
        begin_ = zipIterator(first.begin(), second.begin());

        zipIterator copy(first.begin(), second.begin());
        size_t max_size = std::min(std::distance(first.begin(), first.end()),
                                   std::distance(second.begin(), second.end()));
        for (int i = 0; i < max_size; ++i) {
            ++copy;
        }

        end_ = copy;
    }

    zipIterator begin() {
        return begin_;
    }

    zipIterator end() {
        return end_;
    }

private:
    zipIterator begin_;
    zipIterator end_;
};
