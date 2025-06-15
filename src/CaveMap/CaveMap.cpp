#include "CaveMap.hpp"
#include "CaveMapLoader.hpp"
#include "CaveMapLogic.hpp"
#include "MapRenderer.hpp"

CaveMap::CaveMap(std::unique_ptr<MapLoadStrategy> loader)
    : maploader{std::move(loader)}
{
    tiles = maploader->load();
}

CaveMap::~CaveMap()
{
    maploader->save(tiles);
}

GridCoordinate CaveMap::getCenter() const
{
    return GridCoordinate{tiles.getWidth() / 2, tiles.getHeight() / 2};
}

std::string CaveMap::describeTile(GridCoordinate coord) const
{
    auto tile = tiles.getElement(coord);
    if (!tile.discovered)
    {
        return "Undiscovered";
    }

    return tileTypeToString(tile.getType());
}

CaveMapInterface::ActionList CaveMap::availableCommands(GridCoordinate coord)
{
    ActionList commands{};
    if (tiles.getElement(coord).reachable && canCollapse(tiles, coord))
    {
        commands.emplace_back(std::make_unique<DrillCommand>(*this, coord));
    }

    return commands;
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

void CaveMap::draw(sf::RenderTarget &target) const
{
    MapRenderer mr{target};
    mr.drawTiles(tiles);
    return;
}

void CaveMap::update(ResourceManager<sf::Texture> &tileset)
{
    updateTextures(tiles, tileset, false);
}