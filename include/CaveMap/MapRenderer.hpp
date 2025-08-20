#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include "Grid2D.hpp"
#include "ResourceManager.hpp"

struct TileRenderInfo
{
    sf::Vector2f position;
    bool visible;

    std::shared_ptr<sf::Texture> texture;
    int rotation;
};

class MapRenderer
{
public:
    MapRenderer();

    void update(Grid2D<Tile> &tiles, ResourceManager<sf::Texture> &textures);
    void drawTiles(const Grid2D<Tile> &tiles, sf::RenderTarget &target) const;

private:
    static Grid2D<TileRenderInfo> calculateRenderInfo(const Grid2D<Tile> &tiles);

    void drawTilesInternal(const Grid2D<TileRenderInfo> &renderInfo, sf::RenderTarget &target) const;
    void drawBorder(int width, int height, sf::RenderTarget &target) const;

    Grid2D<TileRenderInfo> renderInfo_;
};
