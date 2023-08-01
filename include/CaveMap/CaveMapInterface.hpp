#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "CaveMapCommon.hpp"
#include "MapCommands.hpp"

class CaveMapInterface
{
public:
    virtual ~CaveMapInterface() = default;

    virtual void draw(sf::RenderTarget &target) const = 0;
    virtual void update() = 0;

    virtual GridCoordinate getCenter() const = 0;

    virtual std::string describeTile(GridCoordinate coord) const = 0;

    using ActionList = std::vector<std::unique_ptr<MapCommand>>;
    virtual ActionList availableCommands(GridCoordinate coord) = 0;
};