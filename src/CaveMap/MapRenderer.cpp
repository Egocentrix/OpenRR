#include "MapRenderer.hpp"
#include "CaveMap.hpp"

MapRenderer::MapRenderer(sf::RenderTarget &target)
    : target_{target}
{
}

void MapRenderer::drawTiles(const Grid2D<Tile> &tiles)
{
    sf::Sprite sprite;
    sprite.setOrigin(TEXSIZE / 2, TEXSIZE / 2);
    sprite.setScale(CaveMap::TILESIZE / TEXSIZE, CaveMap::TILESIZE / TEXSIZE);

    for (int x = 0; x < tiles.getWidth(); x++)
    {
        for (int y = 0; y < tiles.getHeight(); y++)
        {
            const Tile &current = tiles.getElement(x, y);

            if (!current.discovered)
            {
                continue;
            }

            if (current.texture != nullptr)
            {
                sprite.setTexture(*current.texture);
            }
            sprite.setPosition(CaveMap::TILESIZE * (x + 0.5), CaveMap::TILESIZE * (y + 0.5));
            sprite.setRotation(current.rotation * 90);
            target_.draw(sprite);
        }
    }
    sf::RectangleShape border(sf::Vector2f(CaveMap::TILESIZE * tiles.getWidth(), CaveMap::TILESIZE * tiles.getHeight()));
    border.setOutlineColor(sf::Color::White);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(-1.f);
    target_.draw(border);
    return;
}