#pragma once

#include <iostream>

template<typename T>
class xrange {

public:
    class xrangeIterator {
    public:
        typedef typename std::input_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;

        xrangeIterator(const value_type& value, const value_type& step) : value_(value), step_(step) {}

        xrangeIterator& operator++() {
            value_ += step_;
            return *this;
        }

        xrangeIterator operator++(int) {
            value_type tmp = value_;
            ++(*this);
            return xrangeIterator(tmp, step_);
        }

        value_type operator*() const {
            return value_;
        }

        bool operator==(const xrangeIterator& iterator) {
            return value_ == iterator.value_;
        }

        bool operator!=(const xrangeIterator& iterator) {
            value_type default_value{};
            if (step_ > default_value) {
                return value_ < iterator.value_;
            }
            return value_ > iterator.value_;
        }

    private:
        value_type value_;
        value_type step_;
    };

public:
    typedef T value_type;
    typedef xrangeIterator iterator;

    xrange(const value_type& start, const value_type& end) {
        start_ = start;
        end_ = end;
        SetStep();
    }

    explicit xrange(const value_type& end) {
        start_ = value_type{};
        end_ = end;
        SetStep();
    }

    xrange(const value_type& start, const value_type& end, const value_type& step) {
        start_ = start;
        end_ = end;

        value_type default_value{};

        if (start < end and step < default_value or start > end and step > default_value or step == default_value) {
            throw std::runtime_error("Failed to construct xrange");
        }

        step_ = step;
    }

    xrangeIterator begin() {
        return xrangeIterator(start_, step_);
    }

    xrangeIterator end() {
        return xrangeIterator(end_, step_);
    }

protected:
    void SetStep() {
        if (start_ <= end_) {
            value_type default_value{};
            ++default_value;
            step_ = default_value;
        } else {
            value_type default_value{};
            --default_value;
            step_ = default_value;
        }
    }

private:
    value_type start_;
    value_type end_;
    value_type step_;
};