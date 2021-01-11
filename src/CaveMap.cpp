#include <cmath>
#include <fstream>
#include <iostream>

#include "CaveMap.hpp"

CaveMap::CaveMap(int width, int height)
    : tiles{width, height}
{
    for (int i = 0; i < width * height; i++)
    {
        tiles.addElement(Tile(TileType::Wall));
    }
    tiles.getElement(width / 2, height / 2) = Tile(TileType::Floor);
    discover(width / 2, height / 2);
}

CaveMap::~CaveMap()
{
}

void CaveMap::load(const std::string &filename)
{
    // std::ifstream infile;
    // infile.open(filename, std::ios::binary | std::ios::in);

    // if (infile.is_open())
    // {
    //     infile.read((char *)&width, sizeof(int));
    //     infile.read((char *)&height, sizeof(int));

    //     tiles.clear();

    //     tiles.resize(width * height);
    //     infile.read((char *)tiles.data(), sizeof(Tile) * width * height);
    // }

    // infile.close();
}

void CaveMap::save(const std::string &filename)
{
    // std::ofstream outfile;
    // outfile.open(filename, std::ios::binary | std::ios::out);

    // outfile.write((char *)&width, sizeof(int));
    // outfile.write((char *)&height, sizeof(int));

    // outfile.write((char *)tiles.data(), sizeof(Tile) * width * height);

    // outfile.close();
}

Tile &CaveMap::getTile(int x, int y)
{
    return tiles.getElement(x, y);
}

void CaveMap::drill(int x, int y)
{
    if (tiles.isEdgeElement(x, y))
    {
        return;
    }

    if (!getTile(x, y).clickable)
    {
        return;
    }

    if (getTile(x, y).getType() != TileType::Wall)
    {
        return;
    }

    getTile(x, y) = Tile(TileType::Floor); // Visibility defaults to false
    discover(x, y);
}

void CaveMap::discover(int x, int y)
{
    if (!tiles.isInBounds(x, y))
    {
        return;
    }

    Tile &current = tiles.getElement(x, y);
    if (current.discovered)
    {
        return;
    }

    current.discovered = true;
    if (current.getType() == TileType::Wall)
    {
        return;
    }

    for (auto coord : tiles.neighboursOf(x, y, false))
    {
        tiles.getElement(coord.x, coord.y).clickable = true;
    }

    for (auto coord : tiles.neighboursOf(x, y, true))
    {
        if (!isStable(coord.x, coord.y))
        {
            drill(coord.x, coord.y);
        }
        discover(coord.x, coord.y);
    }
}

void CaveMap::draw(sf::RenderTarget &target, TextureManager &textures)
{
    float tilesize = 50;
    int texsize = 128;

    sf::Sprite sprite;
    sprite.setScale(tilesize / texsize, tilesize / texsize);

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
                sprite.setTexture(textures.getRef("floor"));
                break;
            case TileType::Wall:
                sprite.setTexture(textures.getRef("wall"));
                break;
            }

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

bool CaveMap::isStable(int x, int y)
{
    if (tiles.isEdgeElement(x, y))
    {
        return true;
    }

    if (!getTile(x, y).getType() == TileType::Wall)
    {
        return true;
    }

    int supportingwalls = countNeighborsOfType(x, y, {TileType::Wall}, false);

    return supportingwalls >= 2;
}

int CaveMap::countNeighborsOfType(int x, int y, std::vector<TileType> whitelist, bool diagonals)
{
    int result = 0;

    for (auto &coord : tiles.neighboursOf(x, y, diagonals))
    {
        for (auto &type : whitelist)
        {
            if (tiles.getElement(coord.x, coord.y).getType() == type)
            {
                result += 1;
                break;
            }
        }
    }

    return result;
}