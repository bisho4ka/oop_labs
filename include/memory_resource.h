#pragma once
#include <iostream>
#include <memory_resource>
#include "map"

template <size_t PoolSize>
class MemoryResource : public std::pmr::memory_resource {
private:
    unsigned char pool[PoolSize];
    std::map<unsigned char*, size_t> allocated_blocks;
public:
    size_t allocated_block_count() const { 
        return allocated_blocks.size();
    }
    
    void* do_allocate(size_t bytes, size_t alignment) override {
        if (bytes > PoolSize) 
            throw std::bad_alloc(); 

        if (allocated_blocks.empty()) {
            allocated_blocks[pool] = bytes;
            return pool;
        }

        if (allocated_blocks.begin()->first - pool >= bytes) {
            allocated_blocks[pool] = bytes;
            return pool;
        }

        for (auto it = allocated_blocks.begin(); it != --allocated_blocks.end(); it++) {
            unsigned char* firstBlock = it->first + it->second;
            if(std::next(it)->first - firstBlock >= bytes) {
                allocated_blocks[firstBlock] = bytes;
                return firstBlock;
            }
        }

        auto lastBlock = --allocated_blocks.end();
        if(pool + PoolSize - (lastBlock->first + lastBlock->second)) {
            allocated_blocks[lastBlock->first + lastBlock->second] = bytes;
            return lastBlock->first + lastBlock->second;
        }
        throw std::bad_alloc();
    }

    void do_deallocate(void* ptr, size_t bytes, size_t alignment) override {
        unsigned char* block = static_cast<unsigned char*>(ptr);
        if (allocated_blocks.contains(block)){
            allocated_blocks.erase(block);
            return;
        }
        throw std::logic_error("Ошибка удаления");
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
    
    ~MemoryResource() {
        for (const auto& [ptr, size] : allocated_blocks)
            ::operator delete(ptr);
        allocated_blocks.clear();
    }
};