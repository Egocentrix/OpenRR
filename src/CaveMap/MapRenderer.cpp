#include "MapRenderer.hpp"
#include "CaveMap.hpp"

MapRenderer::MapRenderer(sf::RenderTarget &target)
    : target_{target}
{
}

void MapRenderer::drawTiles(const Grid2D<Tile> &tiles)
{
    // Assume all textures are of the same size
    const auto texturesize = sf::Vector2f(tiles.getElement(0, 0).texture->getSize());

    sf::Sprite sprite;
    sprite.setOrigin(texturesize * 0.5f);
    sprite.setScale(1 / texturesize.x, 1 / texturesize.y);

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
            sprite.setPosition(x + 0.5, y + 0.5);
            sprite.setRotation(current.rotation * 90);
            target_.draw(sprite);
        }
    }
    sf::RectangleShape border(sf::Vector2f(tiles.getWidth(), tiles.getHeight()));
    border.setOutlineColor(sf::Color::White);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(-0.5f);
    target_.draw(border);
    return;
}