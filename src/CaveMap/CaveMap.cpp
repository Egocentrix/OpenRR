#include "CaveMap.hpp"
#include "CaveMapLoader.hpp"
#include "CaveMapLogic.hpp"
#include "MapRenderer.hpp"

CaveMap::CaveMap(std::unique_ptr<MapLoadStrategy> loader, ResourceManager<sf::Texture> &texturepack)
    : maploader{std::move(loader)}, tileset{texturepack}
{
    tiles = maploader->load();
}

CaveMap::~CaveMap()
{
    maploader->save(tiles);
}

bool CaveMap::isVisible(int x, int y) const
{
    return isVisible(GridCoordinate{x, y});
}

bool CaveMap::isVisible(GridCoordinate coord) const
{
    return tiles.getElement(coord).discovered;
}

void CaveMap::drill(int x, int y)
{
    drill(GridCoordinate{x, y});
}

void CaveMap::drill(GridCoordinate coord)
{
    if (!tiles.getElement(coord).reachable || !canCollapse(tiles, coord))
    {
        return;
    }

    tiles.getElement(coord) = Tile(TileType::Floor); // Visibility defaults to false
    for (auto tc : tiles.neighbourCoordinates(coord, false))
    {
        recursiveCollapse(tiles, tc);
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
