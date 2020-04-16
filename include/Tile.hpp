#pragma once

enum TileType
{
    Floor,
    Wall
};

class Tile
{
private:
    TileType type;

public:
    Tile() {}
    Tile(TileType type);

    TileType getType() { return type; }
};
