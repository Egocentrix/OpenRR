#include "PathFinder.hpp"

#include <queue>

PathFinder::PathFinder(const Grid2D<Tile> &tiles)
    : tiles_{tiles}
{
}

std::vector<GridCoordinate> PathFinder::findRoute(GridCoordinate start, GridCoordinate destination)
{
    Grid2D<int> distances{tiles_.getWidth(), tiles_.getHeight()};
    size_t numTiles = tiles_.getWidth() * tiles_.getHeight();
    for (size_t i = 0; i < numTiles; ++i)
    {
        distances.addElement(INT_MAX);
    }
    distances.getElement(destination) = 0;

    bool found = false;
    std::queue<GridCoordinate> queue;
    queue.push(destination);
    while (!queue.empty())
    {
        auto current = queue.front();
        queue.pop();
        if (current.x == start.x && current.y == start.y)
        {
            found = true;
            break;
        }
        auto currentDistance = distances.getElement(current);

        for (auto &&node : tiles_.neighbourCoordinates(current, false, false))
        {
            if (tiles_.getElement(node).getType() == TileType::Floor && distances.getElement(node) > currentDistance)
            {
                distances.getElement(node) = currentDistance + 1;
                queue.push(node);
            }
        }
    }

    return found ? calculatePath(distances, start) : std::vector<GridCoordinate>{};
}

using Coordinate = PathGenerator::Coordinate;
std::vector<Coordinate> PathFinder::findRoute(Coordinate start, Coordinate destination)
{
    std::vector<Coordinate> path;
    GridCoordinate startcoordinate{static_cast<int>(start.x), static_cast<int>(start.y)};
    GridCoordinate endcoordinate{static_cast<int>(destination.x), static_cast<int>(destination.y)};
    for (auto &&c : findRoute(startcoordinate, endcoordinate))
    {
        path.push_back(Coordinate{c.x + 0.5f, c.y + 0.5f});
    }
    
    if (!path.empty())
    {
        path.push_back(destination);
    }

    return path;
}

std::vector<GridCoordinate> PathFinder::calculatePath(const Grid2D<int> &distances, GridCoordinate start)
{

    std::vector<GridCoordinate> path{start};
    GridCoordinate current = start;
    while (distances.getElement(current) != 0)
    {
        for (auto &&n : tiles_.neighbourCoordinates(current, false, false))
        {
            if (distances.getElement(n) < distances.getElement(current))
            {
                current = n;
                break;
            }
        }
        path.push_back(current);
    }

    return path;
}
