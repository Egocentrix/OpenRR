#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "CaveMapLoader.hpp"
#include "Grid2D.hpp"
#include "ResourceManager.hpp"
#include "Tile.hpp"
#include "MapCommands.hpp"

// Container for tile objects, and functions for manipulating them.
class CaveMap
{
public:
    static constexpr float TILESIZE = 50.f;

    CaveMap(std::unique_ptr<MapLoadStrategy> loader, ResourceManager<sf::Texture> &texturepack);

    ~CaveMap();

    bool isVisible(GridCoordinate coord) const;

    std::string describeTile(GridCoordinate coord) const;

    using ActionList = std::vector<std::unique_ptr<MapCommand>>;
    ActionList availableCommands(GridCoordinate coord);

    void drill(GridCoordinate coord);

    void draw(sf::RenderTarget &target);

private:
    using TileGrid = Grid2D<Tile>;
    TileGrid tiles;

    std::unique_ptr<MapLoadStrategy> maploader;
    ResourceManager<sf::Texture> &tileset;
};
