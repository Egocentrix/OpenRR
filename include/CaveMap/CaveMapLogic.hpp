#pragma once

#include "Grid2D.hpp"
#include "Tile.hpp"
#include "ResourceManager.hpp"

void updateTexture(Tile &tile, ResourceManager<sf::Texture> &textures);
void updateTextures(Grid2D<Tile> &tiles, ResourceManager<sf::Texture> &textures, bool reset = false);