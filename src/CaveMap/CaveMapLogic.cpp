#include "CaveMapLogic.hpp"

void updateTexture(Tile &tile, ResourceManager<sf::Texture> &textures)
{
    std::string texturename;
    if (tile.getType() == TileType::Floor)
    {
        texturename = "floor";
    }
    if (tile.getType() == TileType::Wall)
    {
        switch (tile.variant)
        {
        case WallVariant::Flat:
            texturename = "wall";
            break;
        case WallVariant::InnerCorner:
            texturename = "wall_incorner";
            break;
        case WallVariant::OuterCorner:
            texturename = "wall_outcorner";
            break;

        default:
            break;
        }
    }
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