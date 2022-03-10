#include "utils.hpp"
#include <filesystem>
#include <set>
#include <string>
#include <string_view>

std::string right_pad(const std::string_view &str, std::size_t length) {
    auto pad_length = length - str.length();
    std::string result(length, ' ');
    std::copy(str.begin(), str.end(), result.begin());
    return result;
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
