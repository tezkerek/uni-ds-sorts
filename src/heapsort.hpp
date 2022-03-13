#include <algorithm>

namespace {

template <typename RandomIt>
RandomIt get_left_child(RandomIt start, RandomIt node) {
    return std::next(start, 2 * std::distance(start, node) + 1);
}

template <typename RandomIt>
void sift_down(RandomIt start, RandomIt end, RandomIt root) {
    auto left_child = get_left_child(start, root);
    while (left_child < end) {
        auto swap_target = root;

        if (*left_child > *swap_target) {
            swap_target = left_child;
        }
        auto right_child = left_child + 1;
        if (right_child < end && *right_child > *swap_target) {
            swap_target = right_child;
        }

        if (swap_target == root) {
            return;
        }

        std::iter_swap(swap_target, root);
        root = swap_target;
        left_child = get_left_child(start, root);
    }
}

template <typename RandomIt> void max_heapify(RandomIt start, RandomIt end) {
    auto n = std::distance(start, end);
    auto last_non_leaf_node = std::next(start, (n - 2) / 2);
    for (auto node = last_non_leaf_node; node >= start; node--) {
        sift_down(start, end, node);
    }
}
} // namespace

namespace sorts {
template <typename RandomIt> void heapsort(RandomIt start, RandomIt end) {
    max_heapify(start, end);

    auto heap_end = end - 1;
    while (heap_end > start) {
        std::iter_swap(heap_end, start);
        sift_down(start, heap_end, start);
        heap_end--;
    }
}
} // namespace sorts
