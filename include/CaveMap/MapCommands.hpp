#pragma once

#include <memory>
#include <string>
#include "Command.hpp"
#include "CaveMapCommon.hpp"
#include "Tile.hpp"
class CaveMap;

// Base classes for Command pattern
class MapCommand : public Command
{
public:
    virtual ~MapCommand() = default;

    virtual std::string describe() const = 0;
    virtual void execute() const = 0;

protected:
    MapCommand(CaveMap &map, const GridCoordinate &coord);

    CaveMap &map_;
    const GridCoordinate coord_;
};

class MapCommandFactory
{
    public:
    MapCommandFactory(CaveMap& map);
    std::unique_ptr<MapCommand> createCommand(GridCoordinate coord, TileAction action);

    private:
    CaveMap& map_;
};

// Specific commands from here
class DrillCommand : public MapCommand
{
public:
    DrillCommand(CaveMap &map, const GridCoordinate &coord);

    std::string describe() const override { return "Drill"; }
    void execute() const override;
};

class EmptyCommand : public MapCommand
{
public:
    EmptyCommand(CaveMap &map, const GridCoordinate &coord) : MapCommand{map, coord} {}

    std::string describe() const override { return "Nothing"; }
    void execute() const override {}
};