#include <catch2/catch_test_macros.hpp>

#include "ResourceManager.hpp"

SCENARIO("Registering and loading resources")
{
    GIVEN("A resource Manager")
    {
        ResourceManager<sf::Font> rm;

        WHEN("I register a resource")
        {
            REQUIRE_NOTHROW(rm.registerResource("resource-id", "../../OpenSans-Regular.ttf"));

            THEN("I can retrieve the registered resource")
            {
                auto resource = rm.getResource("resource-id");
                CHECK(resource != nullptr);
            }
        }

        THEN("Loading an unregistered resource will give an error")
        {
            REQUIRE_THROWS(rm.getResource("unregistered-name"));
        }

        THEN("Attempting to register a non-existing file will give an error")
        {
            REQUIRE_THROWS(rm.registerResource("resource-id", "non-existing.filename"));
        }
    }
}