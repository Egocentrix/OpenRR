#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Grid2D.hpp"
#include "TextureManager.hpp"
#include "Tile.hpp"

// Container for tile objects, and functions for manipulating them.
class CaveMap
{
public:
    CaveMap(int width, int height);

    void load(const std::string &filename);
    void save(const std::string &filename);

    Tile &getTile(int x, int y);
    Tile &getTile(GridCoordinate coord);

    void drill(int x, int y);
    void drill(GridCoordinate coord);

    void draw(sf::RenderTarget &target, TextureManager &textures);

private:
    void discover(GridCoordinate coord);

    bool isStable(GridCoordinate coord);
    int countNeighborsOfType(GridCoordinate coord, const std::vector<TileType> &whitelist, bool diagonals = true);

    Grid2D<Tile> tiles;
};
