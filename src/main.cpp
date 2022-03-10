#include "mergesort.hpp"
#include "radix_sort.hpp"
#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <istream>
#include <set>
#include <vector>

class Test {
private:
    std::size_t n;
    int max_value;
    std::vector<int> values;

public:
    Test() : n(0), max_value(0) {}
    Test(std::size_t n, int max_value) : n(n), max_value(max_value) {
        values.resize(n);
    }

    int get_n() const { return n; }

    int get_max_value() const { return max_value; }

    std::vector<int> &get_values() { return values; }

    friend std::istream &operator>>(std::istream &is, Test &test) {
        is >> test.n >> test.max_value;
        test.values.reserve(test.n);

        for (std::size_t i = 0; i < test.n; i++) {
            int x;
            is >> x;
            test.values.push_back(x);
        }

        return is;
    }
};

using SortFunc = void (*)(std::vector<int>::iterator,
                          std::vector<int>::iterator);

std::chrono::duration<double> run_sort(Test &test, SortFunc sort_fn) {
    // Measure sort duration
    auto start_time = std::chrono::system_clock::now();
    sort_fn(test.get_values().begin(), test.get_values().end());
    auto end_time = std::chrono::system_clock::now();

    return end_time - start_time;
}

const std::vector<std::pair<std::string, SortFunc>> sort_functions = {
    {"radix sort (base 2^16)", sorts::radix_sort<65536>},
    {"radix sort (base 16)", sorts::radix_sort<16>},
    {"radix sort (base 10)", sorts::radix_sort<10>},
    {"mergesort", sorts::mergesort},
};

void test_sorts(Test &test) {
    std::cerr << "n = " << test.get_n() << "; max = " << test.get_max_value()
              << '\n';

    // Compute expected answer using std::sort
    Test expected_test(test);
    auto result = run_sort(expected_test, std::sort);
    std::cout << "✔ std::sort: " << result.count() << '\n';

    for (auto [sort_fn_name, sort_fn] : sort_functions) {
        result = run_sort(test, sort_fn);
        auto matches_expected = test.get_values() == expected_test.get_values();
        std::cout << (matches_expected ? "✔ " : "❌ ") << sort_fn_name << ": "
                  << result.count() << '\n';
    }
}

std::set<std::filesystem::path>
get_files_in_order(const std::filesystem::path &dir_path) {
    std::set<std::filesystem::path> file_paths;
    for (const auto &file_path :
         std::filesystem::directory_iterator(dir_path)) {
        file_paths.insert(file_path.path());
    }

    return file_paths;
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
        std::cerr << "Running " << test_file_path.filename() << '\n';
        std::ifstream test_file_is(test_file_path);

        Test test;
        test_file_is >> test;

        test_sorts(test);

        test_file_is.close();
    }
    return 0;
}
