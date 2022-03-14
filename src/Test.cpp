#include "Test.hpp"

#include <chrono>
#include <cstddef>
#include <istream>
#include <vector>

template <typename Num> Test<Num>::Test() : n(0), max_value(0) {}

template <typename Num>
Test<Num>::Test(std::size_t n, Num max_value) : n(n), max_value(max_value) {
    values.resize(n);
}

template <typename Num> std::size_t Test<Num>::get_n() const { return n; }

template <typename Num> Num Test<Num>::get_max_value() const {
    return max_value;
}

template <typename Num> std::vector<Num> &Test<Num>::get_values() {
    return values;
}

/** Sort the elements using `sort_fn` and return the elapsed time. */
template <typename Num>
std::chrono::duration<double> Test<Num>::run_sort(SortFunc sort_fn) {
    // Measure sort duration
    auto start_time = std::chrono::high_resolution_clock::now();
    sort_fn(get_values().begin(), get_values().end());
    auto end_time = std::chrono::high_resolution_clock::now();

    return end_time - start_time;
}

template <typename Num>
std::istream &operator>>(std::istream &is, Test<Num> &test) {
    is >> test.n >> test.max_value;
    test.values.reserve(test.n);

    for (std::size_t i = 0; i < test.n; i++) {
        int x;
        is >> x;
        test.values.push_back(x);
    }

    return is;
}
