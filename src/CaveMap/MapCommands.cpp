#include "MapCommands.hpp"
#include "CaveMap.hpp"

MapCommand::MapCommand(CaveMap &map, const GridCoordinate &coord)
    : map_{map}, coord_{coord}
{
}

DrillCommand::DrillCommand(CaveMap &map, const GridCoordinate &coord)
    : MapCommand{map, coord}
{
}

void DrillCommand::execute() const
{
    map_.drill(coord_);
}

MapCommandFactory::MapCommandFactory(CaveMap &map)
    : map_{map}
{
}

std::unique_ptr<MapCommand> MapCommandFactory::createCommand(GridCoordinate coord, TileAction action)
{
    switch (action)
    {
    case TileAction::Drill:
        return std::make_unique<DrillCommand>(map_, coord);
        break;

    default:
        return std::make_unique<EmptyCommand>(map_, coord);
        break;
    }
}
