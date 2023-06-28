#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "CaveMapLoader.hpp"
#include "Grid2D.hpp"
#include "ResourceManager.hpp"
#include "Tile.hpp"

// Container for tile objects, and functions for manipulating them.
class CaveMap
{
public:
    static constexpr float TILESIZE = 50.f;

    CaveMap(int width, int height, ResourceManager<sf::Texture> &texturepack);
    CaveMap(std::unique_ptr<CaveMapLoader> loader, ResourceManager<sf::Texture> &texturepack);

    ~CaveMap();

    void load(const std::string &filename);
    void save(const std::string &filename);

    bool isVisible(int x, int y) const;

    void drill(int x, int y);
    void drill(GridCoordinate coord);

    void draw(sf::RenderTarget &target);

private:
    using TileGrid = Grid2D<Tile>;
    TileGrid tiles;

    std::unique_ptr<CaveMapLoader> maploader;
    ResourceManager<sf::Texture> &tileset;
};
