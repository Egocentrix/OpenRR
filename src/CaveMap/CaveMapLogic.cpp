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

void updateTextures(Grid2D<Tile> &tiles, ResourceManager<sf::Texture> &textures, bool reset)
{
    for (Tile &current : tiles)
    {
        if (reset || current.textureneedsupdate)
        {
            updateTexture(current, textures);
        }
    }
}