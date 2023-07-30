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

bool CaveMap::isVisible(GridCoordinate coord) const
{
    return tiles.getElement(coord).discovered;
}

std::string CaveMap::describeTile(GridCoordinate coord) const
{
    std::string description{};
    switch (tiles.getElement(coord).getType())
    {
    case TileType::Floor:
        description += "Floor";
        break;
    case TileType::Wall:
        description += "Wall";
        break;
    }
    return description;
}

CaveMapInterface::ActionList CaveMap::availableCommands(GridCoordinate coord)
{
    ActionList commands{};
    if (true)
    {
        commands.emplace_back(std::make_unique<EmptyCommand>(*this, coord));
    }
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

void CaveMap::update()
{
    updateTextures(tiles, tileset, false);
}