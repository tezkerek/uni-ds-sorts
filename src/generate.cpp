#include <array>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

constexpr std::array<std::pair<std::size_t, std::size_t>, 6> TESTS{{
    {10'000, 1'000'000'000},
    {100'000, 1'000'000'000},
    {100'000'000, 100},
    {100'000'000, 1'000},
    {100'000'000, 1'000'000},
    {100'000'000, 1'000'000'000},
}};

void generate_almost_sorted(std::ostream &os) {
    constexpr auto TEST = TESTS[5];

    std::vector<int> nums(TEST.first);
    auto bool_gen = std::bind(std::uniform_int_distribution<>(0, 1),
                              std::default_random_engine());

    // Generate sorted numbers
    int n = 0;
    for (std::size_t i = 0; i < TEST.first; i++) {
        nums[i] = n;
        if (bool_gen()) {
            n++;
        }
    }

    auto index_gen =
        std::bind(std::uniform_int_distribution<>(0, nums.size() - 1),
                  std::default_random_engine());
    // Randomly invert elements
    for (std::size_t i = 0; i < 10; i++) {
        std::swap(nums[index_gen()], nums[index_gen()]);
    }

    os << TEST.first << ' ' << TEST.second << '\n';
    for (auto x : nums) {
        os << x << ' ';
    }
    os << '\n';
}

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
        auto test_file_name = "test" + std::to_string(test_index) + "_" +
                              std::to_string(test_dimen.first) + "_" +
                              std::to_string(test_dimen.second) + ".txt";
        std::cerr << "Writing to " << test_file_name << '\n';

        auto test_file_path = tests_dir_path / test_file_name;
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

    std::ofstream test_almost_sorted_os(tests_dir_path /
                                        "test_almost_sorted.txt");
    generate_almost_sorted(test_almost_sorted_os);
    test_almost_sorted_os.close();

    return 0;
}
