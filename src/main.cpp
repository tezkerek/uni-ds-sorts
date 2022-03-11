#include "Test.hpp"
#include "mergesort.hpp"
#include "quicksort.hpp"
#include "radix_sort.hpp"
#include "shellsort.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <istream>
#include <string_view>
#include <vector>

using SortFunc = void (*)(std::vector<int>::iterator,
                          std::vector<int>::iterator);
using SortFuncEntry = std::pair<std::string_view, SortFunc>;

constexpr std::array<SortFuncEntry, 6> sort_functions = {{
    {"radix sort (base 2^16)", sorts::radix_sort<65536>},
    {"radix sort (base 16)", sorts::radix_sort<16>},
    {"radix sort (base 10)", sorts::radix_sort<10>},
    {"shellsort", sorts::shellsort<sorts::shellsort_gaps::CIURA>},
    {"quicksort", sorts::quicksort},
    {"mergesort", sorts::mergesort},
}};
constexpr std::size_t MAX_SORT_NAME_LENGTH =
    std::max_element(sort_functions.begin(), sort_functions.end(),
                     [](const SortFuncEntry &p1, const SortFuncEntry &p2) {
                         return p1.first.length() < p2.first.length();
                     })
        ->first.length();

void test_sorts(Test &test) {
    std::cerr << "n = " << test.get_n() << ", max = " << test.get_max_value()
              << '\n';

    // Compute expected answer using std::sort
    Test expected_test(test);
    auto result = expected_test.run_sort(std::sort);
    std::cout << "	✔ " << right_pad("std::sort", MAX_SORT_NAME_LENGTH)
              << " : " << result.count() << '\n';

    for (auto [sort_fn_name, sort_fn] : sort_functions) {
        result = test.run_sort(sort_fn);
        auto matches_expected = test.get_values() == expected_test.get_values();
        std::cout << (matches_expected ? "	✔ " : "	❌ ")
                  << right_pad(sort_fn_name, MAX_SORT_NAME_LENGTH) << " : "
                  << result.count() << '\n';
    }
    std::cout << '\n';
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "USAGE: sorts <tests_dir>\n";
        return 1;
    }

    auto tests_dir_path = std::filesystem::absolute(argv[1]);
    if (!std::filesystem::exists(tests_dir_path)) {
        std::cerr << "Path " << tests_dir_path << " does not exist\n";
        return 2;
    }

    for (const auto &test_file_path : get_files_in_order(tests_dir_path)) {
        std::cerr << "Sorting " << test_file_path.filename() << '\n';
        std::ifstream test_file_is(test_file_path);

        Test test;
        test_file_is >> test;

        test_sorts(test);

        test_file_is.close();
    }
    return 0;
}
