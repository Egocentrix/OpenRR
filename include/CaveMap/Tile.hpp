#pragma once

#include <memory>
#include <variant>
#include <SFML/Graphics/Texture.hpp>

enum class TileType
{
    Floor,
    Wall,
};

enum class FloorType
{
    Floor,
    // lava, water
};

enum class WallVariant
{
    Flat,
    InnerCorner,
    OuterCorner,
    Split,
};

enum class RockType
{
    Solid,
};

struct FloorDetails
{
    FloorType floortype;
    // int rubblelevel
};

struct WallDetails
{
    WallVariant wallvariant;
    RockType rocktype;
    // bool reinforced
};

class Tile
{
public:
    Tile(TileType type);

    TileType getType() const;

    bool discovered{false};
    bool reachable{false};

    int rotation{0};
    std::shared_ptr<sf::Texture> texture;
    bool textureneedsupdate{true};

    std::variant<FloorDetails, WallDetails> details;
};
