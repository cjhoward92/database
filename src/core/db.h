//
// Created by carson on 12/29/21.
//

#ifndef DATABASE_DB_H
#define DATABASE_DB_H

#include <string>
#include <filesystem>

#define OPTIONS_FILE "options.db"
#define TABLES_PATH "tables"

namespace database {

    class Db {
    public:
        Db() = default;
        ~Db() = default;

        void Init(const std::filesystem::path& baseDir);

    private:
        std::filesystem::path _baseDir;
    };

} // end namespace

#endif //DATABASE_DB_H
