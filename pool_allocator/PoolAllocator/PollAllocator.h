#pragma once

#include <algorithm>
#include <vector>

#include "Pool.h"

template<typename T>
class PoolAllocator {
public:
    typedef T value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;

    PoolAllocator(const std::initializer_list<std::pair<int, int>>& list) {
        pools_.resize(list.size());
        int i = 0;
        for (auto& it: list) {
            pools_[i] = new Pool(it.first, it.second * sizeof(T));
            i++;
        }

        std::sort(pools_.begin(), pools_.end(), Pool::Comparator());
    }

    template<typename U>
    PoolAllocator(PoolAllocator<U>& other) noexcept {
        std::vector<Pool*> other_pools = other.GetVectorOfPools();
        pools_.resize(other_pools.size());
        int i = 0;
        for (auto& it: other_pools) {
            pools_[i] = it;
            pools_[i]->IncCounter();
            i++;
        }
    }

    pointer allocate(size_t n) {
        pointer ptr = nullptr;
        int32_t i = FindBestPoolIndex(n);
        while (!ptr and i < pools_.size()) {
            ptr = reinterpret_cast<pointer>(pools_[i]->allocate(NumChunks(pools_[i], n)));
            ++i;
        }

        if (!ptr) {
            throw std::bad_alloc{};
        }

        return ptr;
    }

    void deallocate(pointer ptr, size_t n) {
        int32_t idx = FindPoolIndex(ptr);
        if (idx == -1) {
            throw std::bad_alloc{};
        }

        pools_[idx]->deallocate(reinterpret_cast<char*>(ptr), NumChunks(pools_[idx], n));
    }

    template<typename U>
    bool operator==(const PoolAllocator<U>& other) const {
        return std::equal(pools_.begin(), pools_.end(), other.pools_.begin(), other.pools_.end());
    }

    template<typename U>
    bool operator!=(const PoolAllocator<U>& other) const {
        return !(*this == other);
    }

    std::vector<Pool*> GetVectorOfPools() {
        return pools_;
    }

    ~PoolAllocator() {
        for (auto& it: pools_) {
            if (it->GetCounter() >= 1) {
                it->DecCounter();

                if (it->GetCounter() == 0) {
                    delete it;
                }
            }
        }
    }

protected:
    int32_t FindBestPoolIndex(size_t size) {
        int32_t idx = -1;
        int32_t min_excess = INT32_MAX;
        int32_t cur_excess;

        for (int i = 0; i < pools_.size(); ++i) {
            cur_excess = FindExcess(pools_[i], size);
            if (cur_excess < min_excess) {
                idx = i;
                min_excess = cur_excess;
            }
        }

        return idx;
    }

    int32_t FindPoolIndex(const_pointer ptr) {
        for (int i = 0; i < pools_.size(); ++i) {
            if (pools_[i]->IsPointerValid(reinterpret_cast<const char*>(ptr))) {
                return i;
            }
        }

        return -1;
    }

    int32_t Division(int32_t x, int32_t y) {
        return x / y + (x % y ? 1 : 0);
    }

    int32_t FindExcess(const Pool* pool, size_t size) {
        int32_t memory_need = size * sizeof(T);
        return pool->GetChunkSize() * Division(memory_need, pool->GetChunkSize()) - memory_need;
    }

    int32_t NumChunks(const Pool* pool, size_t size) {
        return Division(size * sizeof(T), pool->GetChunkSize());
    }

private:
    std::vector<Pool*> pools_;
};
