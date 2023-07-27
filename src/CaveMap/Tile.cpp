#include "Tile.hpp"

Tile::Tile(TileType type)
{
    switch (type)
    {
    case TileType::Floor:
        details = FloorDetails{};
        break;
    case TileType::Wall:
        details = WallDetails{};
        break;
    }
    return;
}

TileType Tile::getType() const
{
    struct TileTypeFromDetails
    {
        TileType operator()(const FloorDetails &) { return TileType::Floor; }
        TileType operator()(const WallDetails &) { return TileType::Wall; }
    };

    return std::visit(TileTypeFromDetails{}, details);
}