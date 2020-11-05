#include <fstream>
#include <iostream>
#include <algorithm>

#include "CaveMap.hpp"

CaveMap::CaveMap(int width, int height)
    : tiles{width, height}
{
    for (int i = 0; i < width * height; i++)
    {
        tiles.addElement(Tile(TileType::Wall));
    }
    GridCoordinate center{width / 2, height / 2};
    tiles.getElement(center) = Tile(TileType::Floor);
    discover(center);
}

void CaveMap::load(const std::string &filename)
{
    std::ifstream infile(filename);
    if (!infile.is_open())
    {
        return;
    }

    int width, height;
    infile >> width >> height;

    tiles.resize(width, height);
    for (int i = 0; i < width * height; i++)
    {
        int type;
        infile >> type;
        Tile tile{static_cast<TileType>(type)};
        infile >> tile.discovered;
        infile >> tile.clickable;

        tiles.addElement(tile);
    }
    return;
}

void CaveMap::save(const std::string &filename)
{
    std::ofstream outfile(filename);
    outfile << tiles.getWidth() << " ";
    outfile << tiles.getHeight() << " ";

    std::cout << sizeof(Tile);

    for (const auto &tile : tiles)
    {
        outfile << tile.getType() << " ";
        outfile << tile.discovered << " ";
        outfile << tile.clickable << " ";
    }
    return;
}

Tile &CaveMap::getTile(int x, int y)
{
    return tiles.getElement(x, y);
}

Tile &CaveMap::getTile(GridCoordinate coord)
{
    return getTile(coord.x, coord.y);
}

void CaveMap::drill(int x, int y)
{
    drill(GridCoordinate{x, y});
}

void CaveMap::drill(GridCoordinate coord)
{
    if (tiles.isEdgeElement(coord))
    {
        return;
    }

    Tile &tile = tiles.getElement(coord);

    if (!tile.clickable)
    {
        return;
    }

    if (tile.getType() != TileType::Wall)
    {
        return;
    }

    tile = Tile(TileType::Floor); // Visibility defaults to false
    discover(coord);
    return;
}

void CaveMap::discover(GridCoordinate currentCoords)
{
    if (!tiles.isInBounds(currentCoords))
    {
        return;
    }

    Tile &currentTile = tiles.getElement(currentCoords);
    if (currentTile.discovered)
    {
        return;
    }
    currentTile.discovered = true;

    if (currentTile.getType() != TileType::Floor)
    {
        return;
    }

    for (auto t : tiles.neighboursOf(currentCoords, false))
    {
        t->clickable = true;
    }

    for (auto tc : tiles.neighbourCoordinates(currentCoords, true))
    {
        if (!isStable(tc))
        {
            drill(tc);
        }
        discover(tc);
    }
    return;
}

void CaveMap::draw(sf::RenderTarget &target, TextureManager &textures)
{
    float tilesize = 50;
    int texsize = 128;

    sf::Sprite sprite;
    sprite.setScale(tilesize / texsize, tilesize / texsize);

    auto floortex = textures.getTexture("floor");
    auto walltex = textures.getTexture("wall");

    for (int x = 0; x < tiles.getWidth(); x++)
    {
        for (int y = 0; y < tiles.getHeight(); y++)
        {
            Tile &current = tiles.getElement(x, y);

            if (!current.discovered)
            {
                continue;
            }

            switch (current.getType())
            {
            case TileType::Floor:
                current.texture = textures.getTexture("floor");
                break;
            case TileType::Wall:
                current.texture = textures.getTexture("wall");
                break;
            }

            sprite.setTexture(*current.texture);
            sprite.setPosition(tilesize * x, tilesize * y);
            target.draw(sprite);
        }
    }
    sf::RectangleShape border(sf::Vector2f(tilesize * tiles.getWidth(), tilesize * tiles.getHeight()));
    border.setOutlineColor(sf::Color::White);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(-1.f);
    target.draw(border);
}

bool CaveMap::isStable(GridCoordinate coord)
{
    if (tiles.isEdgeElement(coord))
    {
        return true;
    }

    if (getTile(coord).getType() != TileType::Wall)
    {
        return true;
    }

    int supportingWalls = countNeighborsOfType(coord, {TileType::Wall}, false);
    return supportingWalls >= 2;
}

int CaveMap::countNeighborsOfType(GridCoordinate coord, const std::vector<TileType> &whitelist, bool diagonals)
{
    int result{0};
    for (auto tile : tiles.neighboursOf(coord, diagonals))
    {
        result += std::any_of(whitelist.begin(), whitelist.end(), [tile](TileType type) -> bool {
            return type == tile->getType();
        });
    }

    return result;
}