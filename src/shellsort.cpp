#include "shellsort.hpp"

#include <cmath>

namespace sorts::shellsort_gaps {
std::vector<std::size_t> &ciura(std::size_t size) {
    static std::vector<std::size_t> gaps{1, 4, 10, 23, 57, 132, 301, 701};

    std::size_t new_gap = gaps.back() * 2.25;
    while (new_gap < size) {
        gaps.push_back(new_gap);
        new_gap = gaps.back() * 2.25;
    }

    return gaps;
}

std::vector<std::size_t> &tokuda(std::size_t size) {
    static std::vector<std::size_t> gaps;
    static std::size_t k = 1;

    std::size_t new_gap = 0.2 * (9 * std::pow(9.0 / 4, k - 1) - 4);
    while (new_gap < size) {
        gaps.push_back(new_gap);
        k++;
        new_gap = 0.2 * (9 * std::pow(9.0 / 4, k - 1) - 4);
    }

    return gaps;
}
} // namespace shellsort_gaps
