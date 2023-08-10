#pragma once

#include <string>
#include "Command.hpp"
#include "CaveMapCommon.hpp"
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

class CaveMapController
{
public:
    static void executeCommand(const MapCommand &command)
    {
        command.execute();
    }
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