#include <array>
#include <cstdio>
#include <vector>

namespace sorts {

namespace shellsort_gaps {
    constexpr std::array<std::size_t, 8> CIURA = {701, 301, 132, 57,
                                                  23,  10,  4,   1};
}

template <auto GAPS, typename RandomIt>
void shellsort(RandomIt start, RandomIt end) {
    for (auto gap : GAPS) {
        for (auto it1 = start + gap; it1 != end; it1++) {
            auto it2 = it1;
            while (std::distance(start, it2) >= gap && *(it2 - gap) > *it2) {
                std::iter_swap(it2, it2 - gap);
                it2 -= gap;
            }
        }
    }
}
} // namespace sorts
