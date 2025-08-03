#include <numeric>
#include <ranges>

#include "Tile.hpp"

std::string tileTypeToString(const TileType type)
{
    switch (type)
    {
    case TileType::Floor:
        return "Floor";
        break;
    case TileType::Wall:
        return "Wall";
        break;
    default:
        return "Undefined";
    }
}

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

std::vector<TileAction> Tile::getAvailableActions() const
{
    struct TileActionsFromDetails
    {
        std::vector<TileAction> operator()(const WallDetails &) const
        {
            std::vector<TileAction> actions;
            actions.push_back(TileAction::Drill);
            return actions;
        }

        std::vector<TileAction> operator()(const FloorDetails &) const
        {
            return std::vector<TileAction>{};
        }
    };
    
    return std::visit(TileActionsFromDetails{}, details);
}

void Tile::updateRotation(std::span<bool, 8> neighbourIsFloor)
{
    if (getType() == TileType::Floor)
    {
        rotation = 0;
    }
    else if (getType() == TileType::Wall)
    {
        WallDetails &walldetails = std::get<WallDetails>(details);

        // First count without diagonals
        auto straightNeighbourIsFloor = {neighbourIsFloor[0], neighbourIsFloor[2], neighbourIsFloor[4], neighbourIsFloor[6]};
        auto straightIndex = std::distance(straightNeighbourIsFloor.begin(), std::find(straightNeighbourIsFloor.begin(), straightNeighbourIsFloor.end(), true));
        auto numFloorNeighbours = neighbourIsFloor[0] + neighbourIsFloor[2] + neighbourIsFloor[4] + neighbourIsFloor[6];

        if (numFloorNeighbours == 0)
        {
            // Now include diagonals
            numFloorNeighbours = std::accumulate(neighbourIsFloor.begin(), neighbourIsFloor.end(), 0);
            int index = std::distance(neighbourIsFloor.begin(), std::find(neighbourIsFloor.begin(), neighbourIsFloor.end(), true));

            if (numFloorNeighbours == 1)
            {
                walldetails.wallvariant = WallVariant::InnerCorner;
                rotation = (index / 2 + 3) % 4;
            }
            else if (numFloorNeighbours == 2)
            {
                walldetails.wallvariant = WallVariant::Split;
                rotation = (index / 2) % 4;
            }
        }
        else if (numFloorNeighbours == 1)
        {
            walldetails.wallvariant = WallVariant::Flat;
            rotation = (straightIndex + 2) % 4;
        }
        else if (numFloorNeighbours == 2)
        {
            walldetails.wallvariant = WallVariant::OuterCorner;
            if (neighbourIsFloor[0] && neighbourIsFloor[6])
            {
                straightIndex = 3;
            }
            rotation = (straightIndex + 3) % 4;
        }
        // 3+ floor neighbours means unstable, no need to calculate texture
    }
    textureneedsupdate = true;
}
