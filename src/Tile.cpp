#include "Tile.hpp"

Tile::Tile(TileType type)
    : type(type), discovered(false), clickable(false)
{
    return;
}