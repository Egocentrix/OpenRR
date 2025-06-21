#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "CaveMapCommon.hpp"
#include "Command.hpp"
#include "ResourceManager.hpp"

class CaveMapInterface
{
public:
    virtual ~CaveMapInterface() = default;

    virtual void draw(sf::RenderTarget &target) const = 0;
    virtual void update(ResourceManager<sf::Texture> &textures) = 0;

    virtual GridCoordinate getCenter() const = 0;

    virtual std::string describeTile(GridCoordinate coord) const = 0;

    using ActionList = std::vector<std::unique_ptr<Command>>;
    virtual ActionList getAvailableCommands(GridCoordinate coord) = 0;
};