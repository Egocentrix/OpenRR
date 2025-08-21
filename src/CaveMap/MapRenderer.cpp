#include "MapRenderer.hpp"
#include "CaveMap.hpp"
#include "CaveMapLogic.hpp"

MapRenderer::MapRenderer()
{
}

void MapRenderer::update(Grid2D<Tile> &tiles, ResourceManager<sf::Texture> &textures)
{
    if(renderInfo_.getWidth() == 0 || renderInfo_.getHeight() == 0)
    {
        renderInfo_.resize(tiles.getWidth(), tiles.getHeight());
        for (auto &&tile : tiles)
        {
            renderInfo_.addElement(TileRenderInfo{});
        }
    }

    for (int x = 0; x < tiles.getWidth(); x++)
    {
        for (int y = 0; y < tiles.getHeight(); y++)
        {
            const Tile &current = tiles.getElement(x, y);
            if(current.textureneedsupdate)
            {
                current.textureneedsupdate = false;
                renderInfo_.getElement(x,y) = calculateSingleRenderInfo(current, {x,y}, textures);
            }
        }
    }

}

void MapRenderer::drawTiles(const Grid2D<Tile> &tiles, sf::RenderTarget &target) const
{
    drawTilesInternal(renderInfo_, target);
    drawBorder(tiles.getWidth(), tiles.getHeight(), target);

    return;
}

TileRenderInfo MapRenderer::calculateSingleRenderInfo(const Tile &tile, GridCoordinate coord, ResourceManager<sf::Texture> &textures)
{
    auto texture = textures.getResource(tile.getTextureString());
    tile.textureneedsupdate = false;
    
    return TileRenderInfo{
        .position{static_cast<float>(coord.x), static_cast<float>(coord.y)},
        .visible{tile.discovered},
        .texture{texture},
        .rotation{tile.rotation}};
}

void MapRenderer::drawTilesInternal(const Grid2D<TileRenderInfo> &tiles, sf::RenderTarget &target) const
{
    // Assume all textures are of the same size
    const auto texturesize = sf::Vector2f(tiles.getElement(0, 0).texture->getSize());

    sf::Sprite sprite;
    sprite.setOrigin(texturesize * 0.5f);
    sprite.setScale(1 / texturesize.x, 1 / texturesize.y);

    for (auto &&current : tiles)
    {
        if (!current.visible)
        {
            continue;
        }

        if (current.texture != nullptr)
        {
            sprite.setTexture(*current.texture);
        }
        sprite.setPosition(current.position + sf::Vector2f{0.5f, 0.5f});
        sprite.setRotation(current.rotation * 90);
        target.draw(sprite);
    }
}

void MapRenderer::drawBorder(int width, int height, sf::RenderTarget &target) const
{
    sf::RectangleShape border(sf::Vector2f(width, height));
    border.setOutlineColor(sf::Color::White);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(0.5f);
    target.draw(border);
}