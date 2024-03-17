#pragma once

#include <cstdlib>
#include <cstdint>
#include <memory>

class Pool {
public:
    typedef char* pointer;
    typedef const char* const_pointer;

    Pool() {
        num_of_chunks_ = 0;
        unused_chunks_ = 0;
        chunk_size_ = 0;
        memory_start_ = nullptr;
        used_ = nullptr;
        counter_ = new int32_t[1];
        *counter_ = 1;
    }

    Pool(size_t num_of_chunks, size_t chunk_size) : num_of_chunks_(num_of_chunks), unused_chunks_(num_of_chunks),
                                                    chunk_size_(chunk_size) {
        used_ = new bool[num_of_chunks_]{};
        memory_start_ = new char[num_of_chunks * chunk_size];
        counter_ = new int32_t[1];
        *counter_ = 1;
    }

    pointer allocate(size_t n) {
        if (n > unused_chunks_) {
            return nullptr;
        }
        size_t counter = 0;
        for (size_t i = 0; i < num_of_chunks_; ++i) {
            counter = !used_[i] ? ++counter : 0;
            if (counter == n) {
                for (size_t j = i - n + 1; j < i + 1; ++j) {
                    used_[j] = true;
                }
                unused_chunks_ -= n;
                return memory_start_ + (i - n + 1) * chunk_size_;
            }
        }

        return nullptr;
    }

    void deallocate(const_pointer ptr, size_t n) {
        size_t idx = (ptr - memory_start_) / chunk_size_;

        if (ptr + n > memory_start_ + num_of_chunks_ * chunk_size_) {
            throw std::bad_alloc{};
        }

        for (size_t i = idx; i < idx + n; ++i) {
            used_[i] = false;
        }

        unused_chunks_ += n;
    }

    ~Pool() {
        delete[] memory_start_;
        delete[] used_;
    }

    size_t GetChunkSize() const {
        return chunk_size_;
    }

    void IncCounter() {
        (*counter_)++;
    }
    void DecCounter() {
        (*counter_)--;
    }

    int32_t GetCounter() {
        return *counter_;
    }

    struct Comparator {
        bool operator()(const Pool* first, const Pool* second) const {
            return first->chunk_size_ < second->chunk_size_;
        }
    };

    bool IsPointerValid(const_pointer ptr) {
        return (ptr >= memory_start_ and ptr <= memory_start_ + chunk_size_*num_of_chunks_);
    }

private:
    size_t num_of_chunks_;
    size_t chunk_size_;
    size_t unused_chunks_;
    pointer memory_start_;
    bool* used_;
    int32_t* counter_;
};
