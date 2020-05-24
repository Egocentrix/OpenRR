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

    bool discovered;

    TileType getType() { return type; }
};
