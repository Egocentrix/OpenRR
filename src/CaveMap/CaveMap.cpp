#include "CaveMap.hpp"
#include "CaveMapLoader.hpp"
#include "CaveMapLogic.hpp"
#include "MapRenderer.hpp"

CaveMap::CaveMap(std::unique_ptr<CaveMapLoader> loader, ResourceManager<sf::Texture> &texturepack)
    : maploader{std::move(loader)}, tileset{texturepack}
{
    tiles = maploader->load();
    updateRotations(tiles);
}

CaveMap::~CaveMap()
{
    maploader->save(tiles);
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
