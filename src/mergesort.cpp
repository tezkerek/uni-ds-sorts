#include <vector>

namespace {
template <typename It, typename T>
void merge(const It &start, const It &mid, const It &end) {
    std::vector<T> temp_sorted_vec;
    auto it1 = start;
    auto it2 = mid;

    // Merge overlapping elements
    while (it1 != mid && it2 != end) {
        if (*it1 > *it2) {
            temp_sorted_vec.push_back(*it2);
            ++it2;
        } else {
            temp_sorted_vec.push_back(*it1);
            ++it1;
        }
    }

    // Add remaining elements
    while (it1 != mid) {
        temp_sorted_vec.push_back(*it1);
        ++it1;
    }
    while (it2 != end) {
        temp_sorted_vec.push_back(*it2);
        ++it2;
    }

    std::copy(temp_sorted_vec.begin(), temp_sorted_vec.end(), start);
}
} // namespace

namespace sorts {
template <typename It> void mergesort(const It &start, const It &end) {
    if (std::distance(start, end) == 1) {
        // Stop at a single element
        return;
    }

    auto mid = start + std::distance(start, end) / 2;
    mergesort(start, mid);
    mergesort(mid, end);
    merge(start, mid, end);
}
} // namespace sorts
