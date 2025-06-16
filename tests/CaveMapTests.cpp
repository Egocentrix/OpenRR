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
    }

    SECTION("The center tile is a floor tile")
    {
        REQUIRE(tiles.getElement(width / 2, height / 2).getType() == TileType::Floor);
    }
}

TEST_CASE("Checking a map string for validity", "[maploader]")
{
    SECTION("A rectangular map string is classified valid")
    {
        std::string mapstring = "xxxxx,"
                                "yyyyy,"
                                "zzzzz,";
        bool valid = StringMapLoader::isValid(mapstring);
        CHECK(valid == true);
    }

    GIVEN("A non-rectangular map string")
    {
        std::vector<std::string> mapstrings = {"xxxxxx,"
                                               "yyyyyy,"
                                               "zzzzz,",

                                               "xxxxxx,"
                                               "yyyyy,"
                                               "zzzzzx,",

                                               "xxxxxx,"
                                               "yyyyy,,"
                                               "zzzzzx,"};
        int index = GENERATE(0, 1);
        auto mapstring = mapstrings[index];
        bool valid = StringMapLoader::isValid(mapstring);
        CHECK(valid == false);
    }
}

TEST_CASE("Loading a map from a mapstring", "[maploader]")
{
    std::string mapstring = "wwwwww,"
                            "w---ww,"
                            "w--o-w,"
                            "w----w,"
                            "wwwwww,";

    auto tiles = StringMapLoader(mapstring).load();

    SECTION("Map size is calculated correctly")
    {
        CHECK(tiles.getWidth() == 6);
        CHECK(tiles.getHeight() == 5);
    }

    auto topleft = tiles.getElement(0, 0);
    auto topright = tiles.getElement(5, 0);
    auto toprightinner = tiles.getElement(4, 1);
    auto center = tiles.getElement(3, 2);

    SECTION("The correct tile types are added")
    {
        CHECK(topleft.getType() == TileType::Wall);
        CHECK(topright.getType() == TileType::Wall);
        CHECK(toprightinner.getType() == TileType::Wall);
        CHECK(center.getType() == TileType::Floor);
    }

    SECTION("Map visibility was calculated after loading")
    {
        CHECK(topleft.discovered == true);
        CHECK(topright.discovered == false);
        CHECK(toprightinner.discovered == true);
        CHECK(center.discovered == true);

        CHECK(topleft.reachable == false);
        CHECK(toprightinner.reachable == true);
    }
}

SCENARIO("Drilling walls")
{
    GIVEN("A default cave map")
    {
        CaveMap cavemap{std::make_unique<DefaultMapLoader>(5, 5)};

        GridCoordinate top{0, 2};
        GridCoordinate center{2, 2};
        GridCoordinate tileToDrill{1, 2};

        THEN("An edge tile is not visible and can not be drilled")
        {
            REQUIRE(cavemap.describeTile(top) == "Undiscovered");
            CHECK(cavemap.availableCommands(top).empty());
        }

        WHEN("I check a wall tile next to a floor tile")
        {
            REQUIRE(cavemap.describeTile(center) == "Floor");
            REQUIRE(cavemap.describeTile(tileToDrill) == "Wall");

            auto actions = cavemap.availableCommands(tileToDrill);

            THEN("That tile can be drilled")
            {
                CHECK(actions.size() == 1);
                CHECK(actions[0]->describe() == "Drill");
            }
        }

        WHEN("I drill a wall")
        {
            REQUIRE(cavemap.describeTile(tileToDrill) == "Wall");
            DrillCommand(cavemap, tileToDrill).execute();

            THEN("The drilled wall becomes a floor tile")
            {
                CHECK(cavemap.describeTile(tileToDrill) == "Floor");
            }

            THEN("The edge tile behind it is now discovered but can still not be drilled")
            {
                CHECK(cavemap.describeTile(top) == "Wall");
                CHECK(cavemap.availableCommands(top).empty());
            }
        }
    }
}