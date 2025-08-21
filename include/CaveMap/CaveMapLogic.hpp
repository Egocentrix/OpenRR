#pragma once

#include <vector>

#include "Grid2D.hpp"
#include "Tile.hpp"
#include "ResourceManager.hpp"

using TileGrid = Grid2D<Tile>;

// Functions for updating tile appearance
void updateRotation(TileGrid &tiles, GridCoordinate coord);
void updateRotations(TileGrid &tiles);

// Functions for simulating cave behaviour
void recursiveDiscover(TileGrid &tiles, GridCoordinate start);
void recursiveCollapse(TileGrid &tiles, GridCoordinate start);

bool canCollapse(const TileGrid &tiles, GridCoordinate coord);
bool shouldCollapse(const TileGrid &tiles, GridCoordinate coord);

std::vector<bool> neighbourIsOfType(const TileGrid &tiles,
                                    GridCoordinate center,
                                    TileType type,
                                    bool includeDiagonals);
