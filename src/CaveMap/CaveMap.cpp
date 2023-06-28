#include <fstream>

#include "CaveMap.hpp"
#include "CaveMapLoader.hpp"
#include "CaveMapLogic.hpp"
#include "MapRenderer.hpp"

CaveMap::CaveMap(int width, int height, ResourceManager<sf::Texture> &texturepack)
    : tiles{width, height},
      tileset{texturepack}
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
    FileMapLoader loader{filename};
    tiles = loader.load();
    updateRotations(tiles);
    return;
}

void CaveMap::save(const std::string &filename)
{
    FileMapLoader loader{filename};
    loader.save(tiles);
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

void CaveMap::draw(sf::RenderTarget &target)
{
    updateTextures(tiles, tileset, false);
    MapRenderer mr{target};
    mr.drawTiles(tiles);
    return;
}
