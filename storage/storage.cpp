#include <filesystem>

#include "storage.hpp"

uintmax_t file_len(const std::string path_str) {
    return std::filesystem::file_size(path_str);
}