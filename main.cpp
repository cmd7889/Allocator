#include <iostream>
#include <list>
#include <chrono>
#include <iomanip>

#include "Allocator.h"

int main() {
    using namespace std::chrono;
    using namespace memory;
    std::list<int> default_alloc;
    std::list<int, linear_alloc<int>> my_alloc(linear_alloc<int>(100000000));

    auto start = steady_clock::now();
    for (int i = 0; i < 100000; ++i) {
        default_alloc.push_back(i);
    }
    for (int i = 0; i < 100000; ++i) {
        default_alloc.pop_back();
    }

    auto duration = duration_cast<std::chrono::duration<double, std::milli>>(steady_clock::now() - start);
    std::cout << "Default allocator: "
              << std::setprecision(4)
              << duration.count() << "ms elapsed" << std::endl;

    start = steady_clock::now();
    for (int i = 0; i < 100000; ++i) {
        my_alloc.push_back(i);
    }
    for (int i = 0; i < 100000; ++i) {
        my_alloc.pop_back();
    }

    duration = duration_cast<std::chrono::duration<double, std::milli>>(steady_clock::now() - start);
    std::cout << "My allocator: "
              << std::setprecision(4)
              << duration.count() << "ms elapsed" << std::endl;

}