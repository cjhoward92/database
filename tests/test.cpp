#include <catch2/catch_test_macros.hpp>
#include "state.h"

TEST_CASE("Generates a raft id", "[raft]") {
    raft::initialize_raft_id();
    REQUIRE(raft::get_raft_id().size() > 0);
}