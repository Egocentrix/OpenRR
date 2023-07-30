#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "CaveMapInterface.hpp"

#include "CaveMapLoader.hpp"
#include "Grid2D.hpp"
#include "ResourceManager.hpp"
#include "Tile.hpp"
#include "MapCommands.hpp"

// Container for tile objects, and functions for manipulating them.
class CaveMap : public CaveMapInterface
{
public:
    static constexpr float TILESIZE = 50.f;

    CaveMap(std::unique_ptr<MapLoadStrategy> loader, ResourceManager<sf::Texture> &texturepack);

    ~CaveMap();

    // Implement CaveMapInterface
    void draw(sf::RenderTarget &target) override;

    std::string describeTile(GridCoordinate coord) const override;

    ActionList availableCommands(GridCoordinate coord) override;

    // Other functions
    bool isVisible(GridCoordinate coord) const;
    void drill(GridCoordinate coord);

private:
    using TileGrid = Grid2D<Tile>;
    TileGrid tiles;

    std::unique_ptr<MapLoadStrategy> maploader;
    ResourceManager<sf::Texture> &tileset;
};
