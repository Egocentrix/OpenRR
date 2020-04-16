#pragma once

#include <SFML/Graphics.hpp>

#include "Tile.hpp"

class CaveMap
{
private:
    Tile *tiles;
    bool *discovered;

    const int width;
    const int height;

    bool checkbounds(int i);
    bool checkbounds(int x, int y);

    int linearindex(int x, int y);

    void discover(int x, int y);

public:
    CaveMap(int width, int height);
    ~CaveMap();

    Tile &getTile(int x, int y) { return tiles[linearindex(x, y)]; }

    void drill(int x, int y);

    void draw(sf::RenderTarget &target);
};
