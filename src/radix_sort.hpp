#pragma once

#include <algorithm>
#include <cmath>
#include <vector>

namespace {
constexpr bool is_power_of_two(unsigned n) { return (n & (n - 1)) == 0; }

template <unsigned Base>
constexpr int compute_key(unsigned num, unsigned power_or_shift) {
    if constexpr (is_power_of_two(Base)) {
        // Use bitwise operations
        constexpr unsigned shift = std::log2(Base);
        return (num >> power_or_shift) & (Base - 1);
    } else {
        // Use normal division
        return num / power_or_shift % Base;
    }
};

template <unsigned Base, typename RandomIt>
void counting_sort(RandomIt start, RandomIt end, unsigned power_or_shift) {
    std::vector<int> count(Base, 0);

    for (auto it = start; it != end; it++) {
        auto key = compute_key<Base>(*it, power_or_shift);
        count[key]++;
    }

    // Compute positions
    for (std::size_t i = 1; i < Base; i++) {
        count[i] += count[i - 1];
    }

    std::vector<int> sorted(std::distance(start, end), 0);

    for (auto it = end - 1; it >= start; it--) {
        auto key = compute_key<Base>(*it, power_or_shift);
        sorted[count[key] - 1] = *it;
        count[key]--;
    }

    std::copy(sorted.begin(), sorted.end(), start);
}
} // namespace

namespace sorts {
template <unsigned Base, typename RandomIt>
void radix_sort(RandomIt start, RandomIt end) {
    auto max_num = *std::max_element(start, end);

    if constexpr (is_power_of_two(Base)) {
        // Use bitwise operations
        constexpr auto two_exp = std::log2(Base);
        for (unsigned shift = 0; (1L << shift) <= max_num; shift += two_exp) {
            counting_sort<Base>(start, end, shift);
        }
    } else {
        // Use normal division
        for (unsigned power = 1; max_num / power > 0; power *= Base) {
            counting_sort<Base>(start, end, power);
        }
    }
}
} // namespace sorts
