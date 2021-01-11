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
    Tile(TileType type);

    bool discovered{false};
    bool clickable{false};

    TileType getType() const { return type; }
};
