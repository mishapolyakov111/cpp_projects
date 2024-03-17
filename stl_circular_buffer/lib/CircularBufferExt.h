#include "CircularBuffer.h"

template<typename T, typename Alloc = std::allocator<T>>
class CircularBufferExt : public CircularBuffer<T, Alloc> {
public:
    typedef CircularBuffer<T, Alloc> Base;
public:
    //parent types
    using typename Base::pointer;
    using typename Base::size_type;
    using typename Base::value_type;
    using typename Base::difference_type;
    using typename Base::iterator;
    using typename Base::const_iterator;
private:
    //parent functions
    using Base::CopyData;
    using Base::IncreasePointer;
    using Base::DecreasePointer;
    using Base::InsertBase;
    using Base::AssignBase;
    using Base::PushBackBase;
    using Base::PushFrontBase;

    //parent fields
    using Base::memory_start_;
    using Base::memory_end_;
    using Base::first_;
    using Base::last_;
    using Base::size_;
    using Base::allocator_;

public:
    CircularBufferExt() : Base() {};

    explicit CircularBufferExt(const size_type& capacity) : Base(capacity) {}

    CircularBufferExt(const CircularBufferExt& other) : Base(other) {}

    CircularBufferExt(size_type n, const value_type& t) : Base(n, t) {}

    template<typename InputIterator, typename = std::_RequireInputIter<InputIterator>>
    CircularBufferExt(InputIterator first, InputIterator last) : Base(first, last) {}

    CircularBufferExt(const std::initializer_list<value_type>& list) : Base(list) {}

    iterator insert(const_iterator place, const size_type& n, const value_type& value) {
        difference_type offset = place - this->cbegin();

        while (this->size() + n > this->max_size()) {
            DoubleCapacity();
        }

        iterator tmp = InsertBase(this->cbegin() + offset, n);
        for (int i = 0; i < n; ++i) {
            *tmp = value;
            ++tmp;
        }

        return tmp - n;
    }

    iterator insert(const_iterator place, const value_type& value) {
        return insert(place, 1, value);
    }

    template<typename InputIterator, typename = std::_RequireInputIter<InputIterator>>
    iterator insert(const_iterator place, InputIterator first, InputIterator last) {
        size_type n = last - first;
        difference_type offset = place - this->cbegin();

        while (this->size() + n > this->max_size()) {
            DoubleCapacity();
        }

        iterator tmp = InsertBase(this->cbegin() + offset, n);
        for (int i = 0; i < n; ++i) {
            *(tmp++) = *(first++);
        }

        return tmp - n;
    }

    iterator insert(const_iterator place, const std::initializer_list<value_type>& list) {
        return insert(place, list.begin(), list.end());
    }

    template<typename InputIterator, typename = std::_RequireInputIter<InputIterator>>
    void assign(InputIterator first, InputIterator last) {
        size_type n = last - first;
        while (this->size() + n > this->max_size()) {
            DoubleCapacity();
        }
        AssignBase(last - first);
        CopyData(first, last);
    }

    void assign(const std::initializer_list<value_type>& list) {
        assign(list.begin(), list.end());
    }

    void assign(const size_type& n, const value_type& value) {
        while (this->size() + n > this->max_size()) {
            DoubleCapacity();
        }
        AssignBase(n);
        for (auto& it: *this) {
            it = value;
        }
    }

    void push_back(const value_type& value) {
        if (this->size() >= this->max_size()) {
            DoubleCapacity();
        }

        PushBackBase(value);
    }

    void push_front(const value_type& value) {
        if (this->size() >= this->max_size()) {
            DoubleCapacity();
        }
        PushFrontBase(value);
    }

    void pop_back() {
        if (this->empty()) {
            return;
        }
        last_ = DecreasePointer(last_, 1);
        size_--;
    }

    void pop_front() {
        if (this->empty()) {
            return;
        }
        first_ = IncreasePointer(first_, 1);
        size_--;
    }

protected:
    void DoubleCapacity() {
        pointer old_memory_start = memory_start_;
        size_type old_capacity = this->max_size();
        size_type new_capacity = 2 * old_capacity;

        iterator begin = this->begin();

        pointer new_memory_start = allocator_.allocate(new_capacity + 1);

        for (pointer i = new_memory_start; i < new_memory_start + size_; ++i) {
            *i = *(begin++);
        }

        memory_start_ = new_memory_start;
        first_ = memory_start_;
        last_ = first_ + size_;
        memory_end_ = memory_start_ + new_capacity;

        allocator_.deallocate(old_memory_start, old_capacity);
    }
};