#pragma once

#include <string>

#include "Grid2D.hpp"
#include "Tile.hpp"

class CaveMapLoader
{
public:
    virtual ~CaveMapLoader() = default;
    
    virtual Grid2D<Tile> load() = 0;
    virtual void save(const Grid2D<Tile> &tiles) = 0;

protected:
    Grid2D<Tile> generateDefaultMap(int width = 10, int height = 10);
};

class DefaultMapLoader : public CaveMapLoader
{
public:
    DefaultMapLoader() = default;
    DefaultMapLoader(int width, int height);

    Grid2D<Tile> load() override;
    void save(const Grid2D<Tile> &) override;

private:
    int width_{10}, height_{10};
};

class FileMapLoader : public CaveMapLoader
{
public:
    FileMapLoader(const std::string &filename);

    Grid2D<Tile> load() override;
    void save(const Grid2D<Tile> &tiles) override;

private:
    std::string filename_{};
};
