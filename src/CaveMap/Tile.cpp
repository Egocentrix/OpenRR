#include <numeric>
#include <ranges>

#include "Tile.hpp"

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
        std::vector<TileAction> operator()(const WallDetails &w) const
        {
            std::vector<TileAction> actions;
            actions.push_back(TileAction::Drill);
            if(!w.reinforced){
                actions.push_back(TileAction::Reinforce);
            }
            return actions;
        }

        std::vector<TileAction> operator()(const FloorDetails &) const
        {
            return std::vector<TileAction>{};
        }
    };

    return std::visit(TileActionsFromDetails{}, details);
}

void Tile::reinforce()
{
    struct Reinforce
    {
        void operator()(WallDetails &details)
        {
            details.reinforced = true;
        }
        void operator()(FloorDetails &)
        {
            // Do nothing
        }
    };

    std::visit(Reinforce{}, details);
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

std::string Tile::getDescription() const
{
    if (!discovered)
    {
        return "Undiscovered";
    }

    struct Describe
    {
        std::string operator()(const FloorDetails &) const
        {
            return "Floor";
        }
        std::string operator()(const WallDetails &details) const
        {
            std::string description;
            if (details.reinforced)
            {
                description += "Reinforced ";
            }
            description +=  "Wall";
            return description;
        }
    };
    
    return std::visit(Describe{}, details);
}

std::string Tile::getTextureString() const
{
    struct TextureNameBuilder
    {
        std::string operator()(const FloorDetails &)
        {
            return "floor";
        }

        std::string operator()(const WallDetails &details)
        {
            std::string texturename{};
            switch (details.wallvariant)
            {
            case WallVariant::Flat:
                texturename += "wall";
                break;
            case WallVariant::InnerCorner:
                texturename += "wall_incorner";
                break;
            case WallVariant::OuterCorner:
                texturename += "wall_outcorner";
                break;
            case WallVariant::Split:
                texturename += "wall_split";
                break;
            }
            return texturename;
        }
    };

    return std::visit(TextureNameBuilder{}, details);
}
