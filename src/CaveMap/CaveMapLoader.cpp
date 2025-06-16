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

StringMapLoader::StringMapLoader(const std::string &mapstring)
    : mapstring_{mapstring}
{
}

bool StringMapLoader::isValid(const std::string &mapstring)
{
    // Check if all rows are the same length
    int width = mapstring.find(StringMapLoader::ROW_SEPARATOR_CHAR);
    for (size_t i = width; i < mapstring.size(); i += width + 1)
    {
        if (mapstring[i] != StringMapLoader::ROW_SEPARATOR_CHAR)
        {
            return false;
        }
    }

    // Map should be rectangular
    if (mapstring.size() % (width + 1) != 0)
    {
        return false;
    }

    // One comma per row
    int height = mapstring.size() / (width + 1);
    int separatorcount = std::count(mapstring.begin(), mapstring.end(), StringMapLoader::ROW_SEPARATOR_CHAR);
    if (separatorcount != height)
    {
        return false;
    }

    return true;
}

Grid2D<Tile> StringMapLoader::loadMap()
{
    if (!isValid(mapstring_))
    {
        logger_.Log(LogLevel::Error, "Mapstring is not rectangular");
        return Grid2D<Tile>{};
    }

    int width = mapstring_.find(StringMapLoader::ROW_SEPARATOR_CHAR);
    int height = mapstring_.size() / (width + 1);

    Grid2D<Tile> tiles{width, height};

    for (char tilechar : mapstring_)
    {
        switch (tilechar)
        {
        case ROW_SEPARATOR_CHAR:
            // Do nothing
            break;
        case 'w':
            tiles.addElement(Tile{TileType::Wall});
            break;
        case 'o':
        case '-':
            // Floor. Fallthrough intentional
        default:
            tiles.addElement(Tile{TileType::Floor});
            break;
        }
        
    }

    int originIndex = mapstring_.find('o');
    int originX = originIndex % (width + 1);
    int originY = originIndex / (width + 1);

    recursiveDiscover(tiles, GridCoordinate{originX, originY});

    return tiles;
}

void StringMapLoader::saveMap(const Grid2D<Tile> &tiles)
{

}
