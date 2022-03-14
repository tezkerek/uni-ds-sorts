#pragma once

#include <vector>

namespace sorts {

namespace shellsort_gaps {
std::vector<std::size_t> &ciura(std::size_t size);
std::vector<std::size_t> &tokuda(std::size_t size);
} // namespace shellsort_gaps

template <auto GapFunc, typename RandomIt>
void shellsort(RandomIt start, RandomIt end) {
    auto gaps = GapFunc(std::distance(start, end));

    for (auto gap = gaps.rbegin(); gap != gaps.rend(); std::advance(gap, 1)) {
        for (auto it1 = start + *gap; it1 < end; it1++) {
            auto it2 = it1;
            while (std::distance(start, it2) >= *gap && *(it2 - *gap) > *it2) {
                std::iter_swap(it2, it2 - *gap);
                it2 -= *gap;
            }
        }
    }
}
} // namespace sorts
