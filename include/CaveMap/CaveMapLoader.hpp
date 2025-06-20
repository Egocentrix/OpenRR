#pragma once

#include <string>

#include "Grid2D.hpp"
#include "Tile.hpp"

#include "Logging.hpp"

class MapLoadStrategy
{
public:
    virtual ~MapLoadStrategy() = default;

    Grid2D<Tile> load();
    void save(const Grid2D<Tile> &tiles);

protected:
    Grid2D<Tile> generateDefaultMap(int width = 10, int height = 10);

private:
    virtual Grid2D<Tile> loadMap() = 0;
    virtual void saveMap(const Grid2D<Tile> &tiles) = 0;
};

class DefaultMapLoader : public MapLoadStrategy
{
public:
    DefaultMapLoader() = default;
    DefaultMapLoader(int width, int height);

private:
    Grid2D<Tile> loadMap() override;
    void saveMap(const Grid2D<Tile> &) override;

    int width_{10}, height_{10};
};

class FileMapLoader : public MapLoadStrategy
{
public:
    FileMapLoader(const std::string &filename);

private:
    Grid2D<Tile> loadMap() override;
    void saveMap(const Grid2D<Tile> &tiles) override;

    std::string filename_{};
    Logger logger_{Logger::create("FileMapLoader")};
};

class StringMapLoader : public MapLoadStrategy
{
public:
    StringMapLoader(const std::string &mapstring);

    static bool isValid(const std::string &mapstring);
    static constexpr char ROW_SEPARATOR_CHAR = ',';

private:
    Grid2D<Tile> loadMap() override;
    void saveMap(const Grid2D<Tile> &tiles) override;

    const std::string mapstring_{};
    Logger logger_{Logger::create("StringMapLoader")};
};
