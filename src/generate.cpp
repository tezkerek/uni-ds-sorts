#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

const std::vector<std::pair<std::size_t, std::size_t>> TESTS = {
    {1000, 1000},
    {1'000'000, 1'000'000},
    {10'000'000, 1'000'000},
    {100'000'000, 1'000'000},
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "USAGE: generate <tests_dir>\n";
        return 1;
    }

    auto tests_dir_path = std::filesystem::absolute(argv[1]);
    if (!std::filesystem::exists(tests_dir_path)) {
        std::cerr << "Path " << tests_dir_path << " does not exist\n";
        return 2;
    }
    std::cerr << "Writing to " << tests_dir_path << '\n';

    std::random_device rand_dev;
    std::mt19937 rand_gen(rand_dev());

    for (std::size_t test_index = 0; test_index < TESTS.size(); test_index++) {
        auto test_dimen = TESTS[test_index];

        // Write test file
        auto test_file_path =
            tests_dir_path / ("test" + std::to_string(test_index) + ".txt");
        std::ofstream test_file_os(test_file_path);
        test_file_os << test_dimen.first << ' ' << test_dimen.second << '\n';

        // Write random numbers
        std::uniform_int_distribution<> rand_distr(0, test_dimen.second);

        test_file_os << rand_distr(rand_gen);
        for (std::size_t i = 0; i < test_dimen.first; i++) {
            test_file_os << ' ' << rand_distr(rand_gen);
        }
        test_file_os << '\n';

        test_file_os.close();
    }

    return 0;
}
