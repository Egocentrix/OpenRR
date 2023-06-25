#include "Tile.hpp"

Tile::Tile(TileType type)
    : type_(type)
{
    return;
}

TileType Tile::getType() const {
    return type_;
}