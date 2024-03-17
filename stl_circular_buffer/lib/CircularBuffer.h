#pragma once
#include <iostream>

template<typename T, typename Alloc = std::allocator<T>>
class CircularBuffer {
public:
    template<typename U>
    class CircularIterator {
    public:
        typedef std::random_access_iterator_tag iterator_category;
        typedef U value_type;
        typedef ptrdiff_t difference_type;
        typedef U* pointer;
        typedef U& reference;

        CircularIterator() {
            current_ = nullptr;
            buffer_ = nullptr;
        }

        CircularIterator(pointer p, const CircularBuffer* buffer) {
            current_ = p;
            buffer_ = buffer;
        }

        CircularIterator(CircularIterator& other) {
            current_ = other.current_;
            buffer_ = other.buffer_;
        }

    protected:
        pointer ConvertPointer(const CircularIterator& it) const {
            if (it.current_ < it.buffer_->first_) {
                return it.buffer_->memory_end_ + (it.current_ - it.buffer_->memory_start_ + 1);
            }

            return it.current_;
        }

        pointer ConvertPointer(pointer p) {
            if (p < buffer_->first_) {
                return buffer_->memory_end_ + (p - buffer_->memory_start_ + 1);
            }

            return p;
        }

        bool Valid() {
            pointer converted_current = ConvertPointer(*this);
            return buffer_->first_ <= converted_current and converted_current <= ConvertPointer(buffer_->last_);
        }

    public:
        CircularIterator& operator+=(int n) {
            if (n < 0) {
                return (*this -= -n);
            }

            if (Valid() and n <= ConvertPointer(buffer_->last_) - current_) {
                MoveIterator(n);
                return *this;
            } else {
                std::cerr << "ERROR";
                std::exit(EXIT_FAILURE);
            }
        }

        CircularIterator& operator-=(int n) {
            if (n < 0) {
                return (*this += -n);
            }
            if (Valid() and n <= ConvertPointer(current_) - buffer_->first_) {
                MoveIterator(-n);
                return *this;
            } else {
                std::cerr << "ERROR";
                std::exit(EXIT_FAILURE);
            }
        }

        CircularIterator& operator++() {
            if (current_ == buffer_->last_ and buffer_->last_ != buffer_->first_) {
                current_ = buffer_->first_;
                return *this;
            } else if (current_ == buffer_->memory_end_) {
                current_ = buffer_->memory_start_;
                return *this;
            }

            ++current_;
            return *this;
        }

        CircularIterator operator++(int) {
            pointer tmp = current_;

            if (current_ == buffer_->last_ and buffer_->last_ != buffer_->first_) {
                current_ = buffer_->first_;
            } else if (current_ == buffer_->memory_end_) {
                current_ = buffer_->memory_start_;
            } else {
                ++current_;
            }

            return CircularIterator(tmp, buffer_);
        }

        CircularIterator& operator--() {
            if (current_ == buffer_->first_ and buffer_->last_ != buffer_->first_) {
                current_ = buffer_->last_;
                return *this;
            } else if (current_ == buffer_->memory_start_) {
                current_ = buffer_->memory_end_;
                return *this;
            }

            --current_;
            return *this;
        }

        CircularIterator operator--(int) {
            pointer tmp = current_;

            if (current_ == buffer_->first_ and buffer_->last_ != buffer_->first_) {
                current_ = buffer_->last_;
            } else if (current_ == buffer_->memory_start_) {
                current_ = buffer_->memory_end_;
            } else {
                --current_;
            }

            return CircularIterator(tmp, buffer_);
        }

        CircularIterator operator+(int n) {
            CircularIterator it = *this;
            return it += n;
        }

        CircularIterator operator-(int n) {
            CircularIterator it = *this;
            return it -= n;
        }

        difference_type operator-(const CircularIterator& iterator) {
            return ConvertPointer(*this) - ConvertPointer(iterator);
        }

        reference operator[](int i) {
            return *((*this) + i);
        }

        reference operator*() const {
            return *current_;
        }

        bool operator<(const CircularIterator& iterator) {
            return *this - iterator < 0;
        }

        bool operator>(const CircularIterator& iterator) {
            return *this - iterator > 0;
        }

        bool operator==(const CircularIterator& iterator) {
            return current_ == iterator.current_;
        }

        bool operator!=(const CircularIterator& iterator) {
            return current_ != iterator.current_;
        }

        bool operator<=(const CircularIterator& iterator) {
            return *this < iterator or *this == iterator;
        }

        bool operator>=(const CircularIterator& iterator) {
            return *this > iterator or *this == iterator;
        }

        void MoveIterator(const difference_type& n) {
            if (n > 0) {
                if (current_ + n > buffer_->memory_end_) {
                    current_ = buffer_->memory_start_ + (n - (buffer_->memory_end_ - current_ + 1));
                } else {
                    current_ += n;
                }
            } else {
                if (current_ + n < buffer_->memory_start_) {
                    current_ = buffer_->memory_end_ - ((-n) - (current_ - buffer_->memory_start_ + 1));
                } else {
                    current_ += n;
                }
            }
        }

    private:
        pointer current_;
        const CircularBuffer* buffer_;
    };

public:
    typedef typename std::allocator_traits<Alloc>::template rebind_alloc<T> alloc_type;
    typedef typename std::allocator_traits<alloc_type>::pointer pointer;

    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    typedef CircularIterator<value_type> iterator;
    typedef CircularIterator<const value_type> const_iterator;

protected:
    template<typename InputIterator>
    void CopyData(InputIterator begin, InputIterator end) {
        if (begin >= end) {
            return;
        }
        iterator current = this->begin();
        while (begin != end) {
            *(current++) = *(begin++);
        }
    }

    bool DataEquality(iterator begin, iterator end) const {
        iterator current = this->begin();
        while (begin != end) {
            if (*(current++) != *(begin++)) {
                return false;
            }
        }
        return true;
    }

    void ShiftDataRight(iterator place, const size_type& shift) {
        if (this->empty() or place == this->end()) {
            return;
        }

        iterator current = this->end() - 1;
        iterator tmp;
        while (current >= place and current != this->end()) {
            tmp = current;
            tmp.MoveIterator(shift);
            *(tmp) = *(current--);
        }
    }

    pointer IncreasePointer(pointer p, const size_type& n) {
        if (p + n > memory_end_) {
            p = memory_start_ + (n - (memory_end_ - p + 1));
            return p;
        }
        return p + n;
    }

    pointer DecreasePointer(pointer p, const size_type& n) {
        if (p - n < memory_start_) {
            p = memory_end_ - (n - (p - memory_start_ + 1));
            return p;
        }
        return p - n;
    }

    iterator CastIterator(const_iterator it) {
        iterator beg = this->begin();
        const_iterator cbeg = this->cbegin();
        size_type offset = it - cbeg;
        return beg + offset;
    }

    iterator InsertBase(const_iterator place, const size_type& n) {
        iterator tmp = CastIterator(place);
        ShiftDataRight(tmp, n);
        last_ = IncreasePointer(last_, n);
        size_ += n;

        return tmp;
    }

    void AssignBase(const size_type& n) {
        this->clear();
        last_ = last_ + n;
        size_ = n;
    }

    void PushFrontBase(const value_type& value) {
        first_ = DecreasePointer(first_, 1);
        *first_ = value;
        size_++;
    }

    void PushBackBase(const value_type& value) {
        *last_ = value;
        last_ = IncreasePointer(last_, 1);
        size_++;
    }

public:
    CircularBuffer() {
        size_ = 0;
        memory_start_ = allocator_.allocate(2);
        first_ = memory_start_;
        last_ = memory_start_;
        memory_end_ = memory_start_ + 1;
    }

    CircularBuffer(const CircularBuffer& other) {
        size_ = other.size_;
        memory_start_ = allocator_.allocate(other.max_size() + 1);
        first_ = memory_start_;
        CopyData(other.cbegin(), other.cend());
        last_ = first_ + size_;
        memory_end_ = memory_start_ + other.max_size();
    }

    explicit CircularBuffer(size_type capacity) {
        size_ = 0;
        memory_start_ = allocator_.allocate(capacity + 1);
        first_ = memory_start_;
        last_ = memory_start_;
        memory_end_ = memory_start_ + capacity;
    }

    CircularBuffer(size_type n, const value_type& t) : CircularBuffer(n) {
        last_ = memory_end_;
        size_ = n;
        for (auto& it: *this) {
            it = t;
        }
    }

    template<typename InputIterator, typename = std::_RequireInputIter<InputIterator>>
    CircularBuffer(InputIterator first, InputIterator last) : CircularBuffer(last - first) {
        last_ = memory_end_;
        size_ = last - first;
        CopyData(first, last);
    }

    CircularBuffer(const std::initializer_list<value_type>& list) : CircularBuffer(list.begin(), list.end()) {}

    CircularBuffer& operator=(const CircularBuffer& other) {
        if (this == &other) {
            return *this;
        }
        allocator_.deallocate(memory_start_, this->max_size() + 1);

        size_ = other.size_;
        memory_start_ = allocator_.allocate(other.max_size() + 1);
        first_ = memory_start_;
        last_ = first_ + size_;
        memory_end_ = memory_start_ + other.max_size();
        CopyData(other.cbegin(), other.cend());

        return *this;
    }

    void swap(CircularBuffer& other) {
        std::swap(memory_start_, other.memory_start_);
        std::swap(memory_end_, other.memory_end_);
        std::swap(first_, other.first_);
        std::swap(last_, other.last_);
        std::swap(size_, other.size_);
    }

    iterator begin() const {
        return iterator(first_, this);
    }

    const_iterator cbegin() const {
        return const_iterator(first_, this);
    }

    iterator end() const {
        return iterator(last_, this);
    }

    const_iterator cend() const {
        return const_iterator(last_, this);
    }

    size_type size() const {
        return size_;
    }

    size_type max_size() const {
        return memory_end_ - memory_start_;
    }

    bool empty() const {
        return begin() == end() and size_ == 0;
    }

    bool operator==(const CircularBuffer& other) const {
        return std::equal(this->begin(), this->end(), other.begin(), other.end());
    }

    bool operator!=(const CircularBuffer& other) const {
        return !(*this == other);
    }

    iterator insert(const_iterator place, const value_type& value) {
        return insert(place, 1, value);
    }

    iterator insert(const_iterator place, const size_type& n, const value_type& value) {
        if (this->size() + n > this->max_size()) {
            iterator tmp = iterator();
            return tmp;
        }

        iterator tmp = InsertBase(place, n);
        for (int i = 0; i < n; ++i) {
            *tmp = value;
            ++tmp;
        }

        return tmp - n;
    }

    template<typename InputIterator, typename = std::_RequireInputIter<InputIterator>>
    iterator insert(const_iterator place, InputIterator first, InputIterator last) {
        size_type n = last - first;
        if (this->size() + n > this->max_size()) {
            iterator tmp = iterator();
            return tmp;
        }

        iterator tmp = InsertBase(place, n);
        for (int i = 0; i < n; ++i) {
            *(tmp++) = *(first++);
        }

        return tmp - n;
    }

    iterator insert(const_iterator place, const std::initializer_list<value_type>& list) {
        return insert(place, list.begin(), list.end());
    }

    iterator erase(const_iterator first, const_iterator last) {
        size_type n = last - first;
        if (this->size() - n < 0) {
            iterator tmp = iterator();
            return tmp;
        }

        iterator copy;
        if (last != this->cend()) {
            copy = CastIterator(first);
        } else {
            copy = this->end();
        }

        iterator f = CastIterator(first);
        iterator l = CastIterator(last);
        while (l < this->end()) {
            *(f++) = *(l++);
        }
        last_ = DecreasePointer(last_, n);
        size_ -= n;

        return copy;
    }

    iterator erase(const_iterator p) {
        if (p == this->cend()) {
            iterator tmp = iterator();
            return tmp;
        }
        return erase(p, p + 1);
    }

    template<typename InputIterator, typename = std::_RequireInputIter<InputIterator>>
    void assign(InputIterator first, InputIterator last) {
        if (last - first > this->max_size()) {
            return;
        }
        AssignBase(last - first);
        CopyData(first, last);
    }

    void assign(const std::initializer_list<value_type>& list) {
        assign(list.begin(), list.end());
    }

    void assign(const size_type& n, const value_type& value) {
        if (n > this->max_size()) {
            return;
        }
        AssignBase(n);
        for (auto& it: *this) {
            it = value;
        }
    }

    void push_back(const value_type& value) {
        if (this->size() >= this->max_size()) {
            return;
        }
        PushBackBase(value);
    }

    void push_front(const value_type& value) {
        if (this->size() >= this->max_size()) {
            return;
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

    void clear() {
        first_ = memory_start_;
        last_ = memory_start_;
        size_ = 0;
    }

    ~CircularBuffer() {
        if (memory_start_) {
            allocator_.deallocate(memory_start_, max_size() + 1);
        }
    }

protected:
    alloc_type allocator_;
    pointer memory_start_;
    pointer first_;
    pointer last_;
    pointer memory_end_;
    size_type size_{};
};

template<typename U, typename Alloc>
void swap(CircularBuffer<U, Alloc> lhs, CircularBuffer<U, Alloc> rhs) {
    lhs.swap(rhs);
}