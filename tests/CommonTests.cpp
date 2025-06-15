#include <catch2/catch_test_macros.hpp>

#include "ResourceManager.hpp"

TEST_CASE("Resource Manager")
{
    ResourceManager<sf::Font> rm;

    SECTION("A registered resource can be loaded")
    {
        REQUIRE_NOTHROW(rm.registerResource("resource-id", "../../OpenSans-Regular.ttf"));

        auto resource = rm.getResource("resource-id");
        CHECK(resource != nullptr);
    }

    SECTION("Loading an unregistered resource will give error")
    {
        REQUIRE_THROWS(rm.getResource("unregistered-name"));
    }

    SECTION("Attempting to register a non-existing file will give an error")
    {
        REQUIRE_THROWS(rm.registerResource("resource-id", "non-existing.filename"));
    }
}