#include "mergesort.h"
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <istream>
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

    friend std::istream &operator>>(std::istream &is, Test &test) {
        is >> test.n >> test.max_value;
        test.values.reserve(test.n);

        for (std::size_t i = 0; i < test.n; i++) {
            is >> test.values[i];
        }

        return is;
    }
};

Test load_test(std::ifstream &test_file_is) {
    Test test;
    test_file_is >> test;

    return test;
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

    for (const auto &test_file_path :
         std::filesystem::directory_iterator(tests_dir_path)) {
        std::ifstream test_file_is(test_file_path.path());

        test_file_is.close();
    }
    return 0;
}
