#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include "Grid2D.hpp"

class MapRenderer
{
public:
    MapRenderer(sf::RenderTarget &target);

    void drawTiles(const Grid2D<Tile> &tiles);

private:
    sf::RenderTarget &target_;
};