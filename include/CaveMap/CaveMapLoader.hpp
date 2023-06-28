#pragma once

#include <string>
#include <memory>

#include "Grid2D.hpp"
#include "Tile.hpp"

class CaveMapLoader
{
public:
    virtual Grid2D<Tile> load() = 0;
    virtual void save(const Grid2D<Tile> &tiles) = 0;

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
