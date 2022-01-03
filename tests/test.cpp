#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "port.h"

using namespace database;

TEST_CASE("Creates a file", "[port]") {
    std::filesystem::path tmpPath("/tmp/test-db-file");
    File::Create(tmpPath);
    assert(std::filesystem::exists(tmpPath));
    unlink(tmpPath.c_str());
}