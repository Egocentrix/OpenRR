#pragma once

class CaveMap;
class GridCoordinate;

// Base classes for Command pattern
class MapCommand
{
public:
    virtual ~MapCommand() = default;

    virtual void execute() const = 0;
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

    void execute() const override;

private:
    CaveMap &map_;
    const GridCoordinate &coord_;
};