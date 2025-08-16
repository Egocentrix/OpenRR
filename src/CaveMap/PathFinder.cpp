#include "PathFinder.hpp"

PathFinder::PathFinder(const Grid2D<Tile> &tiles)
    : tiles_{tiles}
{
}

std::vector<GridCoordinate> PathFinder::findRoute(GridCoordinate start, GridCoordinate destination)
{
    return std::vector<GridCoordinate>{start, destination};
}

using Coordinate = PathGenerator::Coordinate;
std::vector<Coordinate> PathFinder::findRoute(Coordinate start, Coordinate destination)
{
    return std::vector<Coordinate>{start, destination};
}
