#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Grid2D.hpp"
#include "ResourceManager.hpp"
#include "Tile.hpp"

// Container for tile objects, and functions for manipulating them.
class CaveMap
{
public:
    static constexpr float TILESIZE = 50.f;

    CaveMap(int width, int height);

    void load(const std::string &filename);
    void save(const std::string &filename);

    bool isVisible(int x, int y) const;

    void drill(int x, int y);
    void drill(GridCoordinate coord);

    void draw(sf::RenderTarget &target, ResourceManager<sf::Texture> &textures);

private:
    void discover(GridCoordinate coord);
    void updateRotation(GridCoordinate coord);
    void updateAll();

    bool isStable(GridCoordinate coord);
    std::vector<bool> neighbourIsOfType(GridCoordinate coord, const std::vector<TileType> &whitelist, bool diagonals = true);

    using TileGrid = Grid2D<Tile>;
    TileGrid tiles;
};
