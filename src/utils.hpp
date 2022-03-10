#include <filesystem>
#include <set>
#include <string>
#include <string_view>

std::string right_pad(const std::string_view &str, std::size_t length);

std::set<std::filesystem::path>
get_files_in_order(const std::filesystem::path &dir_path);
