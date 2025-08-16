#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class PathGenerator
{
public:
    virtual ~PathGenerator() = default;

    using Coordinate = sf::Vector2f;
    virtual std::vector<Coordinate> findRoute(Coordinate start, Coordinate destination) = 0;
};
