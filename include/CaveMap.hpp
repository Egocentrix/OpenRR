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

    bool isStable(int x, int y);

    int countNeighborsOfType(int x, int y, std::vector<TileType> whitelist, bool diagonals = false);

public:
    CaveMap(int width, int height);
    ~CaveMap();

    void load(const std::string &filename);
    void save(const std::string &filename);

    Tile &getTile(int x, int y); 

    void drill(int x, int y);

    void draw(sf::RenderTarget &target, TextureManager &textures);
};
