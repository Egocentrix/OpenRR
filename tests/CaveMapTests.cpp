#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "CaveMap.hpp"
#include "CaveMapLoader.hpp"
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

TEST_CASE("Loading a new default map")
{
    const int width = GENERATE(3, 10, 21);
    const int height = GENERATE(3, 9, 20);

    DefaultMapLoader ml{width, height};
    auto tiles = ml.load();

    SECTION("Map should have correct size")
    {
        REQUIRE(tiles.getWidth() == width);
        REQUIRE(tiles.getHeight() == height);
    }

    SECTION("Edge tiles must be walls")
    {
        REQUIRE(tiles.getElement(0, height / 2).getType() == TileType::Wall);
        REQUIRE(tiles.getElement(width - 1, height - 1).getType() == TileType::Wall);
        REQUIRE(tiles.getElement(width / 2, height / 2).getType() == TileType::Floor);
    }
}

TEST_CASE("Drilling walls")
{
    CaveMap cavemap{std::make_unique<DefaultMapLoader>(5, 5)};

    GridCoordinate top{0, 2};
    GridCoordinate center{2, 2};
    GridCoordinate tileToDrill{1, 2};

    SECTION("Edge tile can not be drilled")
    {
        REQUIRE(cavemap.describeTile(top) == "Undiscovered");
        REQUIRE(cavemap.availableCommands(top).empty());
    }
    SECTION("Discovered tiles can be drilled")
    {
        REQUIRE(cavemap.describeTile(center) == "Floor");
        REQUIRE(cavemap.describeTile(tileToDrill) == "Wall");

        auto actions = cavemap.availableCommands(tileToDrill);
        CHECK(actions.size() == 1);
        CHECK(actions[0]->describe() == "Drill");
    }

    SECTION("Drilling a tile expands the cave")
    {
        REQUIRE(cavemap.describeTile(tileToDrill) == "Wall");
        DrillCommand(cavemap, tileToDrill).execute();
        CHECK(cavemap.describeTile(tileToDrill) == "Floor");

        // Edge tile is now discovered but can still not be drilled.
        CHECK(cavemap.describeTile(top) == "Wall"); 
        CHECK(cavemap.availableCommands(top).empty());
    }
}