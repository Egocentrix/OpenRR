#include <catch2/catch_test_macros.hpp>

#include "ResourceManager.hpp"

TEST_CASE("Resource Manager")
{
    ResourceManager<sf::Font> rm;

    SECTION("Loading an unregistered resource will give error")
    {
        REQUIRE_THROWS(rm.getResource("unregistered-name"));
    }

    SECTION("A registered resource can be loaded")
    {
        rm.registerResource("resource-id", "../../OpenSans-Regular.ttf");
        auto resource = rm.getResource("resource-id");
        REQUIRE(resource != nullptr);
    }
    
}