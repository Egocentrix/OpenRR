#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include "Grid2D.hpp"

struct TileRenderInfo
{
    GridCoordinate position;
    bool visible;
    
    std::shared_ptr<sf::Texture> texture;
    int rotation;
};

class MapRenderer
{
public:
    MapRenderer();

    void drawTiles(const Grid2D<Tile> &tiles, sf::RenderTarget &target);
};
