#include <string>

#include "CaveMapLogic.hpp"

void updateRotation(TileGrid &tiles, GridCoordinate coord)
{
    Tile &current = tiles.getElement(coord);
    auto neighbours = tiles.neighboursOf(coord, true, true);
    bool isfloor[8];
    std::transform(neighbours.begin(), neighbours.end(), isfloor, [](Tile* t){ return t->getType() == TileType::Floor;});
    current.updateRotation(isfloor);    
}

void updateRotations(TileGrid &tiles)
{
    for (int x = 0; x < tiles.getWidth(); x++)
    {
        for (int y = 0; y < tiles.getHeight(); y++)
        {
            updateRotation(tiles, GridCoordinate{x, y});
        }
    }
}

void recursiveDiscover(TileGrid &tiles, GridCoordinate start)
{
    if (!tiles.isInBounds(start) || tiles.getElement(start).discovered)
    {
        return;
    }

    Tile &current = tiles.getElement(start);
    current.discovered = true;

    if (current.getType() == TileType::Floor)
    {
        for (auto tc : tiles.neighbourCoordinates(start, false))
        {
            tiles.getElement(tc).reachable = true;
        }
        for (auto tc : tiles.neighbourCoordinates(start, true))
        {
            recursiveDiscover(tiles, tc);
        }
    }
}

void recursiveCollapse(TileGrid &tiles, GridCoordinate start)
{
    if (!shouldCollapse(tiles, start))
    {
        return;
    }

    tiles.getElement(start) = Tile(TileType::Floor);
    for (auto tc : tiles.neighbourCoordinates(start, false))
    {
        recursiveCollapse(tiles, tc);
    }
}

bool canCollapse(const TileGrid &tiles, GridCoordinate coord)
{
    return !(tiles.isEdgeElement(coord) || tiles.getElement(coord).getType() == TileType::Floor);
}

bool shouldCollapse(const TileGrid &tiles, GridCoordinate coord)
{
    if (!canCollapse(tiles, coord))
    {
        return false;
    }

    std::vector<bool> isFloor = neighbourIsOfType(tiles, coord, TileType::Floor, false);
    return (isFloor[0] && isFloor[2]) || (isFloor[1] && isFloor[3]);
}

std::vector<bool> neighbourIsOfType(const TileGrid &tiles,
                                    GridCoordinate center,
                                    TileType type,
                                    bool includeDiagonals)
{
    auto neighbours = tiles.neighbourCoordinates(center, includeDiagonals, true);
    std::vector<bool> isMatch{};
    for (auto coord : neighbours)
    {
        isMatch.push_back(tiles.getElement(coord).getType() == type);
    }
    return isMatch;
}