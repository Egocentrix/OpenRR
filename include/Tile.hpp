#pragma once

#include <memory>
#include <SFML/Graphics/Texture.hpp>

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
    std::shared_ptr<sf::Texture> texture;
    int rotation{0};
    bool textureneedsupdate{true};

private:
    TileType type_;
};
