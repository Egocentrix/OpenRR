#pragma once

#include <vector>

#include "Grid2D.hpp"
#include "Tile.hpp"
#include "ResourceManager.hpp"

using TileGrid = Grid2D<Tile>;

// Functions for simulating tile appearance
void updateTexture(Tile &tile, ResourceManager<sf::Texture> &textures);
void updateTextures(TileGrid &tiles, ResourceManager<sf::Texture> &textures, bool reset = false);

void recursiveDiscover(TileGrid &tiles, GridCoordinate start);
void recursiveCollapse(TileGrid &tiles, GridCoordinate start);

std::vector<bool> neighbourIsOfType(const TileGrid &tiles,
                                    GridCoordinate center,
                                    TileType type,
                                    bool includeDiagonals);
