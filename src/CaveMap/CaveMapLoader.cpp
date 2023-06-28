#include <fstream>
#include <iostream>

#include "CaveMapLoader.hpp"
#include "CaveMapLogic.hpp"

Grid2D<Tile> CaveMapLoader::generateDefaultMap(int width, int height)
{
    Grid2D<Tile> tiles{width, height};
    for (int i = 0; i < width * height; i++)
    {
        tiles.addElement(Tile(TileType::Wall));
    }
    GridCoordinate center{width / 2, height / 2};
    tiles.getElement(center) = Tile(TileType::Floor);
    recursiveDiscover(tiles, center);
    return tiles;
}

FileMapLoader::FileMapLoader(const std::string &filename)
    : filename_{filename}
{
}

Grid2D<Tile> FileMapLoader::load()
{
    std::ifstream infile(filename_);
    if (!infile.is_open())
    {
        std::cerr << "could not open file: " << filename_ << std::endl;
        return generateDefaultMap();
    }

    int width, height;
    infile >> width >> height;

    Grid2D<Tile> tiles{width, height};
    for (int i = 0; i < width * height; i++)
    {
        int type;
        infile >> type;
        Tile tile{static_cast<TileType>(type)};
        infile >> tile.discovered;
        infile >> tile.reachable;

        tiles.addElement(tile);
    }
    return tiles;
}

void FileMapLoader::save(const Grid2D<Tile> &tiles)
{
    std::ofstream outfile(filename_);
    outfile << tiles.getWidth() << " ";
    outfile << tiles.getHeight() << " ";

    for (const auto &tile : tiles)
    {
        outfile << tile.getType() << " ";
        outfile << tile.discovered << " ";
        outfile << tile.reachable << " ";
    }
    return;
}
