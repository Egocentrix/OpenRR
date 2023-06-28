#include <fstream>

#include "CaveMap.hpp"
#include "CaveMapLogic.hpp"
#include "MapRenderer.hpp"

CaveMap::CaveMap(int width, int height)
    : tiles{width, height}
{
    for (int i = 0; i < width * height; i++)
    {
        tiles.addElement(Tile(TileType::Wall));
    }
    GridCoordinate center{width / 2, height / 2};
    tiles.getElement(center) = Tile(TileType::Floor);
    recursiveDiscover(tiles, center);
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
        infile >> tile.reachable;

        tiles.addElement(tile);
    }
    updateRotations(tiles);
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
        outfile << tile.reachable << " ";
    }
    return;
}

bool CaveMap::isVisible(int x, int y) const
{
    return tiles.getElement(x, y).discovered;
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

    if (!tile.reachable)
    {
        return;
    }

    if (tile.getType() != TileType::Wall)
    {
        return;
    }

    tile = Tile(TileType::Floor); // Visibility defaults to false
    for (auto tc : tiles.neighbourCoordinates(coord, false))
    {
        if (shouldCollapse(tiles, tc))
        {
            drill(tc);
        }
    }
    recursiveDiscover(tiles, coord);
    updateRotations(tiles);
    return;
}

void CaveMap::draw(sf::RenderTarget &target, ResourceManager<sf::Texture> &textures)
{
    updateTextures(tiles, textures, false);
    MapRenderer mr{target};
    mr.drawTiles(tiles);
    return;
}

