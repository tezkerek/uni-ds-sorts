#include <algorithm>
#include <cmath>
#include <vector>

constexpr bool is_power_of_two(unsigned n) { return (n & (n - 1)) == 0; }

namespace sorts {

template <unsigned Base>
inline int compute_key(unsigned num, unsigned power_or_shift) {
    if constexpr (is_power_of_two(Base)) {
        constexpr unsigned shift = std::log2(Base);
        return (num >> power_or_shift) & (Base - 1);
    } else {
        return num / power_or_shift % Base;
    }
};

using It = std::vector<int>::iterator;
template <unsigned Base>
void counting_sort(It start, It end, unsigned power_or_shift) {
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
    auto rstart = std::reverse_iterator(start);
    auto rend = std::reverse_iterator(end);
    for (auto it = end - 1; it >= start; it--) {
        auto key = compute_key<Base>(*it, power_or_shift);
        sorted[count[key] - 1] = *it;
        count[key]--;
    }

    std::copy(sorted.begin(), sorted.end(), start);
}

/** Radix sort using division */
template <unsigned Base> void radix_sort(It start, It end) {
    auto max_num = *std::max_element(start, end);

    if constexpr (is_power_of_two(Base)) {
        constexpr auto two_exp = std::log2(Base);
        for (unsigned shift = 0; (1L << shift) <= max_num; shift += two_exp) {
            counting_sort<Base>(start, end, shift);
        }
    } else {
        for (unsigned power = 1; max_num / power > 0; power *= Base) {
            counting_sort<Base>(start, end, power);
        }
    }
}
} // namespace sorts
