#include <iostream>
#include <compare>
#include <filesystem>

#include "storage.hpp"
#include "db_config.h"

int main() {
    std::cout << "Hello world!" << std::endl;
    std::cout << "Version: " << Database_VERSION_MAJOR << "." << Database_VERSION_MINOR << std::endl;

    auto cwd = std::filesystem::current_path() / "Database";
    std::cout << "Found file: " << cwd.filename() << std::endl;

    uintmax_t fsz = file_len(cwd.c_str());
    std::cout << "File size: " << fsz << std::endl;

    return 0;
}