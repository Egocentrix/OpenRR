#include <fstream>

#include "CaveMapLoader.hpp"
#include "CaveMapLogic.hpp"

Grid2D<Tile> MapLoadStrategy::generateDefaultMap(int width, int height)
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

Grid2D<Tile> MapLoadStrategy::load()
{
    Grid2D<Tile> tiles = loadMap();
    updateRotations(tiles);
    return tiles;
}

void MapLoadStrategy::save(const Grid2D<Tile> &tiles)
{
    saveMap(tiles);
}

DefaultMapLoader::DefaultMapLoader(int width, int height)
    : width_{width}, height_{height}
{
}

Grid2D<Tile> DefaultMapLoader::loadMap()
{
    return generateDefaultMap(width_, height_);
}

void DefaultMapLoader::saveMap(const Grid2D<Tile> &)
{
}

FileMapLoader::FileMapLoader(const std::string &filename)
    : filename_{filename}
{
}

Grid2D<Tile> FileMapLoader::loadMap()
{
    std::ifstream infile(filename_);
    if (!infile.is_open())
    {
        logger_.Log(LogLevel::Error, "Could not open file: " + filename_ + ". Generating default map...");
        return generateDefaultMap();
    }

    logger_.Log(LogLevel::Info, "Loading map from file: " + filename_);

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

void FileMapLoader::saveMap(const Grid2D<Tile> &tiles)
{
    std::ofstream outfile(filename_);
    outfile << tiles.getWidth() << " ";
    outfile << tiles.getHeight() << " ";

    for (const auto &tile : tiles)
    {
        outfile << static_cast<int>(tile.getType()) << " ";
        outfile << tile.discovered << " ";
        outfile << tile.reachable << " ";
    }
    return;
}
