#include <fstream>
#include <iostream>
#include <algorithm>
#include <numeric>

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
    sprite.setOrigin(texsize / 2, texsize / 2);
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

            updateTexture({x, y}, textures);

            if (current.texture != nullptr)
            {
                sprite.setTexture(*current.texture);
            }
            sprite.setPosition(tilesize * (x + 0.5), tilesize * (y + 0.5));
            sprite.setRotation(current.rotation * 90);
            target.draw(sprite);
        }
    }
    sf::RectangleShape border(sf::Vector2f(tilesize * tiles.getWidth(), tilesize * tiles.getHeight()));
    border.setOutlineColor(sf::Color::White);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(-1.f);
    target.draw(border);
    return;
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

    std::vector<bool> isWall = neighbourIsOfType(coord, {TileType::Wall}, false);
    return (isWall[0] || isWall[2]) && (isWall[1] || isWall[3]);
}

std::vector<bool> CaveMap::neighbourIsOfType(GridCoordinate coord, const std::vector<TileType> &whitelist, bool diagonals)
{
    std::vector<bool> isMatch(diagonals ? 8 : 4);
    auto neighbours = tiles.neighboursOf(coord, diagonals, true);
    std::transform(neighbours.begin(), neighbours.end(), isMatch.begin(), [&](Tile *t) {
        return std::any_of(whitelist.begin(), whitelist.end(), [t](TileType type) {
            return t->getType() == type;
        });
    });
    return isMatch;
}

void CaveMap::updateTexture(GridCoordinate coord, TextureManager &textures)
{
    Tile &tile = getTile(coord);

    if (tile.getType() == TileType::Floor)
    {
        tile.texture = textures.getTexture("floor");
        tile.rotation = 0;
        return;
    }

    auto isFloor = neighbourIsOfType(coord, {TileType::Floor}, false);
    int numFloorNeighbours = std::accumulate(isFloor.begin(), isFloor.end(), 0);

    if (numFloorNeighbours == 0)
    {
        tile.texture = textures.getTexture("wall_incorner");
        isFloor = neighbourIsOfType(coord, {TileType::Floor}, true);
        int index = std::distance(isFloor.begin(), std::find(isFloor.begin(), isFloor.end(), true));
        tile.rotation = (index/2 + 3) % 4;
    }
    else if (numFloorNeighbours == 1)
    {
        tile.texture = textures.getTexture("wall");
        int index = std::distance(isFloor.begin(), std::find(isFloor.begin(), isFloor.end(), true));
        tile.rotation = (index + 2) % 4;
    }
    else if (numFloorNeighbours == 2)
    {
        tile.texture = textures.getTexture("wall_outcorner");
        int index = std::distance(isFloor.begin(), std::find(isFloor.begin(), isFloor.end(), true));
        if (isFloor[0] && isFloor[3])
        {
            index = 3;
        }
        tile.rotation = (index + 3) % 4;
    }
    // 3+ floor neighbours means unstable, no need to calculate texture

    return;
}
