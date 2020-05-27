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
    bool clickable;

    TileType getType() { return type; }
};
