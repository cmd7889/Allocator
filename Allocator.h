//
// Created by ivan on 28.05.22.
//

#ifndef PR_5_ALLOCATOR_H
#define PR_5_ALLOCATOR_H

#include <stdexcept>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <cstdint>
#include <cstdlib>

namespace memory {
    template<typename T>
    class linear_alloc {
    private:
        std::shared_ptr<void> memory;
        std::size_t free_index;
        std::size_t size;

    public:
        using pointer = T*;
        using value_type = T;
        template<typename U>
        struct rebind {
            using other = linear_alloc<U>;
        };
        linear_alloc(std::size_t size = 1024)
                : memory(std::shared_ptr<void>(std::malloc(size),
                                               [](void* ptr) { std::free(ptr); })),
                  free_index(0),
                  size(size)
        {}

        bool operator==(const linear_alloc& rhs) {
            return memory == rhs.memory;
        }

        const std::shared_ptr<void>& get_heap() const {
            return memory;
        }

        std::size_t get_free_ptr() const {
            return free_index;
        }

        std::size_t get_size() const {
            return size;
        }

        template<typename U>
        linear_alloc(const linear_alloc<U>& other) :
                memory(other.get_heap()),
                free_index(other.get_free_ptr()),
                size(other.get_size())
        {}

        T* allocate(std::size_t n) {

            if (free_index + n * sizeof(n) > size) {
                throw std::bad_alloc();
            }

            T* tmp = (T*)((char*)memory.get() + free_index);
            free_index += n * sizeof(T);

            return tmp;

        }

        void deallocate(T* p, std::size_t) {}

    };
}

#endif //PR_5_ALLOCATOR_H
