#include <cmath>
#include <fstream>

#include "CaveMap.hpp"

CaveMap::CaveMap(int width, int height)
    : width(width), height(height)
{
    for (int i = 0; i < width * height; i++)
    {
        tiles.push_back(Tile(TileType::Wall));
    }
    tiles[linearindex(width / 2, height / 2)] = Tile(TileType::Floor);
    discover(width / 2, height / 2);
}

CaveMap::~CaveMap()
{
}

void CaveMap::load(const std::string &filename)
{
    std::ifstream infile;
    infile.open(filename, std::ios::binary | std::ios::in);

    if (infile.is_open())
    {
        infile.read((char *)&width, sizeof(int));
        infile.read((char *)&height, sizeof(int));

        tiles.clear();

        tiles.resize(width * height);
        infile.read((char *)tiles.data(), sizeof(Tile) * width * height);
    }

    infile.close();
}

void CaveMap::save(const std::string &filename)
{
    std::ofstream outfile;
    outfile.open(filename, std::ios::binary | std::ios::out);

    outfile.write((char *)&width, sizeof(int));
    outfile.write((char *)&height, sizeof(int));

    outfile.write((char *)tiles.data(), sizeof(Tile) * width * height);

    outfile.close();
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

    getTile(x, y) = Tile(TileType::Floor); // Visibility defaults to false
    discover(x, y);
}

void CaveMap::discover(int x, int y)
{
    if (!checkbounds(x, y))
    {
        return;
    }

    Tile &current = getTile(x, y);
    if (current.discovered)
    {
        return;
    }

    current.discovered = true;
    if (current.getType() == TileType::Wall)
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

void CaveMap::draw(sf::RenderTarget &target, TextureManager &textures)
{
    float tilesize = 50;
    int texsize = 128;

    sf::Sprite sprite;
    sprite.setScale(tilesize / texsize, tilesize / texsize);

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if (!tiles[linearindex(x, y)].discovered)
            {
                continue;
            }

            switch (tiles[linearindex(x, y)].getType())
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
    sf::RectangleShape border(sf::Vector2f(tilesize * width, tilesize * height));
    border.setOutlineColor(sf::Color::White);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(-1.f);
    target.draw(border);
}
