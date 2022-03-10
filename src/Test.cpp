#include "Test.hpp"
#include <chrono>
#include <cstddef>
#include <istream>
#include <vector>

Test::Test() : n(0), max_value(0) {}

Test::Test(std::size_t n, int max_value) : n(n), max_value(max_value) {
    values.resize(n);
}

int Test::get_n() const { return n; }

int Test::get_max_value() const { return max_value; }

std::vector<int> &Test::get_values() { return values; }

/** Sort the elements using `sort_fn` and return the elapsed time. */
std::chrono::duration<double> Test::run_sort(SortFunc sort_fn) {
    // Measure sort duration
    auto start_time = std::chrono::system_clock::now();
    sort_fn(get_values().begin(), get_values().end());
    auto end_time = std::chrono::system_clock::now();

    return end_time - start_time;
}

std::istream &operator>>(std::istream &is, Test &test) {
    is >> test.n >> test.max_value;
    test.values.reserve(test.n);

    for (std::size_t i = 0; i < test.n; i++) {
        int x;
        is >> x;
        test.values.push_back(x);
    }

    return is;
}
