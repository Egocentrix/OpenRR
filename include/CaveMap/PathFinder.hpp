#pragma once

#include <vector>

#include "CaveMapCommon.hpp"
#include "PathGenerator.hpp"
#include "Grid2D.hpp"
#include "Tile.hpp"

class PathFinder : public PathGenerator
{

public:
    PathFinder(const Grid2D<Tile> &tiles);

    std::vector<GridCoordinate> findRoute(GridCoordinate start, GridCoordinate destination);

    virtual std::vector<Coordinate> findRoute(Coordinate start, Coordinate destination) override;

private:
    const Grid2D<Tile> &tiles_;
};
