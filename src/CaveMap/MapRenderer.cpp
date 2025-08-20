#include "MapRenderer.hpp"
#include "CaveMap.hpp"
#include "CaveMapLogic.hpp"

MapRenderer::MapRenderer()
{
}

void MapRenderer::update(Grid2D<Tile> &tiles, ResourceManager<sf::Texture> &textures)
{
    updateTextures(tiles, textures, false);
    renderInfo_ = calculateRenderInfo(tiles);
}

void MapRenderer::drawTiles(const Grid2D<Tile> &tiles, sf::RenderTarget &target) const
{
    drawTilesInternal(renderInfo_, target);
    drawBorder(tiles.getWidth(), tiles.getHeight(), target);

    return;
}

Grid2D<TileRenderInfo> MapRenderer::calculateRenderInfo(const Grid2D<Tile> &tiles)
{
    Grid2D<TileRenderInfo> renderInfo{tiles.getWidth(), tiles.getHeight()};

    for (int x = 0; x < tiles.getWidth(); x++)
    {
        for (int y = 0; y < tiles.getHeight(); y++)
        {
            const Tile &current = tiles.getElement(x, y);

            renderInfo.addElement(TileRenderInfo{
                .position{static_cast<float>(x), static_cast<float>(y)},
                .visible{current.discovered},
                .texture{current.texture},
                .rotation{current.rotation},
            });
        }
    }

    return renderInfo;
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