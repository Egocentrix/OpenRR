#include <numeric>
#include <string>

#include "CaveMapLogic.hpp"

void updateTexture(Tile &tile, ResourceManager<sf::Texture> &textures)
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

    std::string texturename = std::visit(TextureNameBuilder{}, tile.details);
    tile.texture = textures.getResource(texturename);
    tile.textureneedsupdate = false;
}

void updateTextures(TileGrid &tiles, ResourceManager<sf::Texture> &textures, bool reset)
{
    for (Tile &current : tiles)
    {
        if (reset || current.textureneedsupdate)
        {
            updateTexture(current, textures);
        }
    }
}

void updateRotation(TileGrid &tiles, GridCoordinate coord)
{
    Tile &current = tiles.getElement(coord);

    if (current.getType() == TileType::Floor)
    {
        current.rotation = 0;
    }
    else if (current.getType() == TileType::Wall)
    {
        WallDetails &details = std::get<WallDetails>(current.details);
        auto isFloor = neighbourIsOfType(tiles, coord, TileType::Floor, false);
        int numFloorNeighbours = std::accumulate(isFloor.begin(), isFloor.end(), 0);

        if (numFloorNeighbours == 0)
        {
            // Now include diagonals
            isFloor = neighbourIsOfType(tiles, coord, TileType::Floor, true);
            numFloorNeighbours = std::accumulate(isFloor.begin(), isFloor.end(), 0);
            int index = std::distance(isFloor.begin(), std::find(isFloor.begin(), isFloor.end(), true));

            if (numFloorNeighbours == 1)
            {
                details.wallvariant = WallVariant::InnerCorner;
                current.rotation = (index / 2 + 3) % 4;
            }
            else if (numFloorNeighbours == 2)
            {
                details.wallvariant = WallVariant::Split;
                current.rotation = (index / 2) % 4;
            }
        }
        else if (numFloorNeighbours == 1)
        {
            details.wallvariant = WallVariant::Flat;
            int index = std::distance(isFloor.begin(), std::find(isFloor.begin(), isFloor.end(), true));
            current.rotation = (index + 2) % 4;
        }
        else if (numFloorNeighbours == 2)
        {
            details.wallvariant = WallVariant::OuterCorner;
            int index = std::distance(isFloor.begin(), std::find(isFloor.begin(), isFloor.end(), true));
            if (isFloor[0] && isFloor[3])
            {
                index = 3;
            }
            current.rotation = (index + 3) % 4;
        }
        // 3+ floor neighbours means unstable, no need to calculate texture
    }
    current.textureneedsupdate = true;
}

void updateRotations(TileGrid &tiles)
{
    for (int x = 0; x < tiles.getWidth(); x++)
    {
        for (int y = 0; y < tiles.getHeight(); y++)
        {
            updateRotation(tiles, GridCoordinate{x, y});
        }
    }
}

void recursiveDiscover(TileGrid &tiles, GridCoordinate start)
{
    if (!tiles.isInBounds(start) || tiles.getElement(start).discovered)
    {
        return;
    }

    Tile &current = tiles.getElement(start);
    current.discovered = true;

    if (current.getType() == TileType::Floor)
    {
        for (auto tc : tiles.neighbourCoordinates(start, false))
        {
            tiles.getElement(tc).reachable = true;
        }
        for (auto tc : tiles.neighbourCoordinates(start, true))
        {
            recursiveDiscover(tiles, tc);
        }
    }
}

void recursiveCollapse(TileGrid &tiles, GridCoordinate start)
{
    if (!shouldCollapse(tiles, start))
    {
        return;
    }

    tiles.getElement(start) = Tile(TileType::Floor);
    for (auto tc : tiles.neighbourCoordinates(start, false))
    {
        recursiveCollapse(tiles, tc);
    }
}

bool canCollapse(const TileGrid &tiles, GridCoordinate coord)
{
    return !(tiles.isEdgeElement(coord) || tiles.getElement(coord).getType() == TileType::Floor);
}

bool shouldCollapse(const TileGrid &tiles, GridCoordinate coord)
{
    if (!canCollapse(tiles, coord))
    {
        return false;
    }

    std::vector<bool> isFloor = neighbourIsOfType(tiles, coord, TileType::Floor, false);
    return (isFloor[0] && isFloor[2]) || (isFloor[1] && isFloor[3]);
}

std::vector<bool> neighbourIsOfType(const TileGrid &tiles,
                                    GridCoordinate center,
                                    TileType type,
                                    bool includeDiagonals)
{
    auto neighbours = tiles.neighbourCoordinates(center, includeDiagonals, true);
    std::vector<bool> isMatch{};
    for (auto coord : neighbours)
    {
        isMatch.push_back(tiles.getElement(coord).getType() == type);
    }
    return isMatch;
}