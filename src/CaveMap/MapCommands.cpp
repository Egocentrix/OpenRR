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