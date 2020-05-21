#include <cmath>
#include <fstream>

#include "CaveMap.hpp"

CaveMap::CaveMap(int width, int height)
    : width(width), height(height)
{
    for (int i = 0; i < width * height; i++)
    {
        tiles.push_back(Tile(TileType::Wall));
        discovered.push_back(false);
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
        discovered.clear();

        tiles.resize(width * height);
        infile.read((char *)tiles.data(), sizeof(Tile) * width * height);

        discovered.resize(width * height);
        infile.read((char *)discovered.data(), sizeof(char) * width * height);
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
    outfile.write((char *)discovered.data(), sizeof(char) * width * height);

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

void CaveMap::draw(sf::RenderTarget &target, const std::map<std::string, sf::Texture> &textures)
{
    float tilesize = 50;
    int texsize = 128;

    sf::Sprite sprite;
    sprite.setScale(tilesize / texsize, tilesize / texsize);

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if (!discovered[linearindex(x, y)])
            {
                continue;
            }

            switch (tiles[linearindex(x, y)].getType())
            {
            case TileType::Floor:
                sprite.setTexture(textures.at("floor"));
                break;
            case TileType::Wall:
                sprite.setTexture(textures.at("wall"));
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
