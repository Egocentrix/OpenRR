#include <cmath>

#include "CaveMap.hpp"

CaveMap::CaveMap(int width, int height)
    : width(width), height(height), tiles(new Tile[width * height]), discovered(new bool[width * height])
{
    for (int i = 0; i < width * height; i++)
    {
        tiles[i] = Tile(TileType::Wall);
        discovered[i] = false;
    }
    tiles[linearindex(width / 2, height / 2)] = Tile(TileType::Floor);
    discover(width / 2, height / 2);
}

CaveMap::~CaveMap()
{
    delete[] tiles;
    delete[] discovered;
}

int CaveMap::linearindex(int x, int y)
{
    return checkbounds(x, y) ? x + width * y : 0;
}

bool CaveMap::checkbounds(int i)
{
    return i >= 0 && i < width * height;
}

bool CaveMap::checkbounds(int x, int y)
{
    return x >= 0 && x < width && y >= 0 && y < height;
}

void CaveMap::drill(int x, int y)
{
    if (getTile(x, y).getType() != TileType::Wall)
    {
        return;
    }

    getTile(x, y) = Tile(TileType::Floor);
    discovered[linearindex(x, y)] = false;
    discover(x, y);
}

void CaveMap::discover(int x, int y)
{
    if (discovered[linearindex(x, y)] || !checkbounds(x, y))
    {
        return;
    }
    discovered[linearindex(x, y)] = true;

    if (getTile(x, y).getType() == TileType::Wall)
    {
        return;
    }

    int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

    for (int i = 0; i < 8; i++)
    {
        discover(x + dx[i], y + dy[i]);
    }
}

void CaveMap::draw(sf::RenderTarget &target)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            sf::RectangleShape rect(sf::Vector2f(50, 50));
            rect.setOutlineColor(sf::Color::White);
            rect.setOutlineThickness(-2.f);

            if (!discovered[linearindex(x, y)])
            {
                continue;
            }

            switch (tiles[linearindex(x, y)].getType())
            {
            case TileType::Floor:
                rect.setFillColor(sf::Color::Blue);
                break;
            case TileType::Wall:
                rect.setFillColor(sf::Color::Red);
                break;
            }

            rect.setPosition(50 * x, 50 * y);
            target.draw(rect);
        }
    }
}