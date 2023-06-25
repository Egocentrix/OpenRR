#pragma once

#include <memory>
#include <SFML/Graphics/Texture.hpp>

enum TileType
{
    Floor,
    Wall
};

enum WallVariant
{
    Flat,
    InnerCorner,
    OuterCorner,
};

class Tile
{
public:
    Tile(TileType type);

    TileType getType() const;

    bool discovered{false};
    bool clickable{false};

    WallVariant variant{WallVariant::Flat};
    int rotation{0};

    std::shared_ptr<sf::Texture> texture;
    bool textureneedsupdate{true};

private:
    TileType type_;
};
