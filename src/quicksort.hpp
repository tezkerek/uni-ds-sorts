#pragma once

#include <iterator>

namespace {
template <typename RandomIt>
RandomIt median_of_3(RandomIt start, RandomIt end) {
    auto mid = start + std::distance(start, end) / 2;
    auto last = end - 1;

    if (*mid < *start) {
        std::iter_swap(mid, start);
    }
    if (*last < *start) {
        std::iter_swap(last, start);
    }
    if (*mid < *last) {
        std::iter_swap(mid, last);
    }

    return last;
}

template <typename RandomIt>
RandomIt hoare_partition(RandomIt start, RandomIt end) {
    auto pivot = median_of_3(start, end);

    auto i = start - 1;
    auto j = end;

    while (true) {
        do {
            i++;
        } while (*i < *pivot);
        do {
            j--;
        } while (*j > *pivot);

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
    quicksort(start, pivot);
    quicksort(pivot + 1, end);
}
} // namespace sorts
