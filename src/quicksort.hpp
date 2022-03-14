#pragma once

#include <iterator>

namespace {
template <typename RandomIt>
RandomIt median_of_3(RandomIt start, RandomIt end) {
    auto last = end - 1;
    auto mid = start + std::distance(start, last) / 2;

    if (*mid < *start) {
        std::iter_swap(mid, start);
    }
    if (*last < *start) {
        std::iter_swap(last, start);
    }
    if (*last < *mid) {
        std::iter_swap(mid, last);
    }

    return mid;
}

template <typename RandomIt>
RandomIt hoare_partition(RandomIt start, RandomIt end) {
    auto pivot = median_of_3(start, end);
    auto pivot_val = *pivot;

    auto i = start - 1;
    auto j = end;

    while (true) {
        do {
            i++;
        } while (*i < pivot_val);
        do {
            j--;
        } while (*j > pivot_val);

        if (i >= j)
            return j;
        std::iter_swap(i, j);
    }
}
} // namespace

namespace sorts {
template <typename RandomIt> void quicksort(RandomIt start, RandomIt end) {
    if (std::distance(start, end) <= 1) {
        // Stop at a single element
        return;
    }

    auto pivot = hoare_partition(start, end);
    quicksort(start, pivot + 1);
    quicksort(pivot + 1, end);
}
} // namespace sorts
