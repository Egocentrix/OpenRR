#pragma once

#include <memory>
#include <span>
#include <variant>
#include <SFML/Graphics/Texture.hpp>

enum class TileType
{
    Floor,
    Wall,
};

std::string tileTypeToString(const TileType type);

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

enum class TileAction
{
    Drill,
    // Clear rubble, reinforce, build
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
    std::vector<TileAction> getAvailableActions() const;

    void updateRotation(std::span<bool, 8> neighbourIsFloor);

    bool discovered{false};
    bool reachable{false};

    int rotation{0};
    std::shared_ptr<sf::Texture> texture;
    bool textureneedsupdate{true};

    std::variant<FloorDetails, WallDetails> details;
};
