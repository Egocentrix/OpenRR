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
    CaveMap(int width, int height);

    void load(const std::string &filename);
    void save(const std::string &filename);

    Tile &getTile(int x, int y);
    Tile &getTile(GridCoordinate coord);

    void drill(int x, int y);
    void drill(GridCoordinate coord);

    void draw(sf::RenderTarget &target, ResourceManager<sf::Texture> &textures);

    Grid2D<Tile> tiles;

private:
    void discover(GridCoordinate coord);
    void updateRotation(GridCoordinate coord);

    bool isStable(GridCoordinate coord);
    std::vector<bool> neighbourIsOfType(GridCoordinate coord, const std::vector<TileType> &whitelist, bool diagonals = true);
};

class MapRenderer
{
public:
    MapRenderer(sf::RenderTarget &target);

    void draw(CaveMap &map);

    static constexpr float TILESIZE = 50.f;
    static constexpr float TEXSIZE = 128.f;

private:
    sf::RenderTarget &target_;
};

void updateTexture(Tile &tile, ResourceManager<sf::Texture> &textures);
void updateTextures(CaveMap &map, ResourceManager<sf::Texture> &textures, bool reset = false);
