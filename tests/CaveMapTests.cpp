#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "Tile.hpp"

TEST_CASE("Creating a new tile")
{
    TileType testType = GENERATE(TileType::Floor, TileType::Wall);
    Tile t{testType};
    
    SECTION("Default values must be set correctly")
    {
        REQUIRE(t.discovered == false);
        REQUIRE(t.reachable == false);
        REQUIRE(t.textureneedsupdate == true);
    }

    SECTION("TileType should be set correctly")
    {
        REQUIRE(t.getType() == testType);
    }
}