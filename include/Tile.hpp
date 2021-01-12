#pragma once

enum TileType
{
    Floor,
    Wall
};

class Tile
{
public:
    Tile(TileType type);

    TileType getType() const { return type_; }

    bool discovered{false};
    bool clickable{false};

private:
    TileType type_;
};
