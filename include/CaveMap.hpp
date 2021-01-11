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
private:
    Grid2D<Tile> tiles;

    void discover(int x, int y);
    void discover(GridCoordinate coord);

    bool isStable(int x, int y);
    bool isStable(GridCoordinate coord);

    int countNeighborsOfType(int x, int y, std::vector<TileType> whitelist, bool diagonals = false);
    int countNeighborsOfType(GridCoordinate coord, std::vector<TileType> whitelist, bool diagonals = false);

public:
    CaveMap(int width, int height);

    void load(const std::string &filename);
    void save(const std::string &filename);

    Tile &getTile(int x, int y);
    Tile &getTile(GridCoordinate coord);

    void drill(int x, int y);
    void drill(GridCoordinate coord);

    void draw(sf::RenderTarget &target, TextureManager &textures);
};
