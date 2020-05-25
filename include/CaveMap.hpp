#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "TextureManager.hpp"
#include "Tile.hpp"

// Container for tile objects, and functions for manipulating them.
class CaveMap
{
private:
    std::vector<Tile> tiles;

    int width;
    int height;

    bool checkbounds(int i);
    bool checkbounds(int x, int y);

    int linearindex(int x, int y);

    void discover(int x, int y);

    bool isStable(int x, int y);

public:
    CaveMap(int width, int height);
    ~CaveMap();

    void load(const std::string &filename);
    void save(const std::string &filename);

    Tile &getTile(int x, int y) { return tiles[linearindex(x, y)]; }

    void drill(int x, int y);

    void draw(sf::RenderTarget &target, TextureManager &textures);
};
