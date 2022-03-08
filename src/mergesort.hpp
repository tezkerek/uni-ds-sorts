#pragma once

#include <cstdio>
#include <vector>

namespace {

template <typename It, typename BufIt>
void merge(const It start, const It mid, const It end, const BufIt buffer) {
    auto it1 = start;
    auto it2 = mid;
    auto it_buf = buffer;

    // Merge overlapping elements
    while (it1 != mid && it2 != end) {
        if (*it1 > *it2) {
            *it_buf = *it2;
            ++it2;
        } else {
            *it_buf = *it1;
            ++it1;
        }
        ++it_buf;
    }

    // Add remaining elements
    std::move(it1, mid, it_buf);
    std::move(it2, end, it_buf);

    // Copy back
    std::move(buffer, buffer + std::distance(start, end), start);
}

template <typename It, typename BufIt>
void mergesort_buffer(const It start, const It end, const BufIt buffer) {
    if (std::distance(start, end) <= 1) {
        // Stop at a single element
        return;
    }

    auto mid = start + std::distance(start, end) / 2;
    mergesort_buffer(start, mid, buffer);
    mergesort_buffer(mid, end, buffer);
    merge(start, mid, end, buffer);
}
} // namespace

namespace sorts {
template <typename It> void mergesort(const It start, const It end) {
    using ValueType = typename std::iterator_traits<It>::value_type;
    std::vector<ValueType> buffer(start, end);
    mergesort_buffer(start, end, buffer.begin());
}
} // namespace sorts
