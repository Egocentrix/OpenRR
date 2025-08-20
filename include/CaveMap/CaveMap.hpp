#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "CaveMapInterface.hpp"

#include "CaveMapLoader.hpp"
#include "Grid2D.hpp"
#include "MapCommands.hpp"
#include "MapRenderer.hpp"
#include "PathFinder.hpp"
#include "ResourceManager.hpp"
#include "Tile.hpp"

// Container for tile objects, and functions for manipulating them.
class CaveMap : public CaveMapInterface
{
public:
    CaveMap(std::unique_ptr<MapLoadStrategy> loader);

    ~CaveMap();

    // Implement CaveMapInterface
    void draw(sf::RenderTarget &target) const override;
    void update(ResourceManager<sf::Texture> &tileset) override;

    GridCoordinate getCenter() const override;

    std::string describeTile(GridCoordinate coord) const override;

    ActionList getAvailableCommands(GridCoordinate coord) override;

    PathGenerator& getPathGenerator() override;

    // Other functions
    void drill(GridCoordinate coord);

private:
    using TileGrid = Grid2D<Tile>;
    TileGrid tiles;

    std::unique_ptr<MapLoadStrategy> maploader;
    std::unique_ptr<PathFinder> pathfinder;
    MapRenderer maprenderer;
};
