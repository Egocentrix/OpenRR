#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "Tile.hpp"

class CaveMap
{
private:
    Tile *tiles;
    bool *discovered;

    int width;
    int height;

    bool checkbounds(int i);
    bool checkbounds(int x, int y);

    int linearindex(int x, int y);

    void discover(int x, int y);

public:
    CaveMap(int width, int height);
    ~CaveMap();

    void load(const std::string &filename);
    void save(const std::string &filename);

    Tile &getTile(int x, int y) { return tiles[linearindex(x, y)]; }
    bool isDiscovered(int x, int y) { return discovered[linearindex(x, y)]; }

    void drill(int x, int y);

    void draw(sf::RenderTarget &target);
};
