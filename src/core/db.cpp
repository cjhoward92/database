//
// Created by carson on 12/29/21.
//

/**
 * This file represents the main database implementation. It's the class
 * that represents a database in its entirety. The file structure is as follows:
 *
 * <root>/options.db - The database options config file
 */

#include "db.h"
#include "../port/port.h"

#include <stdexcept>
#include <string>

using namespace database;

void Db::Init(const std::filesystem::path& baseDir) {
    bool exists = std::filesystem::exists(baseDir);

    if (exists && !std::filesystem::is_directory(baseDir)) {
        throw std::invalid_argument("baseDir must be a directory");
    } else if (!exists) {
        if (!std::filesystem::create_directory(baseDir)) {
            throw std::runtime_error("Could not create directory");
        }
    }

    std::filesystem::path optionsPath = baseDir / std::string_view (OPTIONS_FILE);
    if (!std::filesystem::exists(optionsPath)) {
        File::Create(optionsPath);
    }

    std::filesystem::path tablesPath = baseDir / std::string_view (TABLES_PATH);
    if (!std::filesystem::exists(tablesPath)) {
        if (!std::filesystem::create_directory(tablesPath)) {
            throw std::runtime_error("Could not create tables directory");
        }
    }

    this->_baseDir = baseDir;
}