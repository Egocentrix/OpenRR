#include "MapCommands.hpp"
#include "CaveMap.hpp"

DrillCommand::DrillCommand(CaveMap &map, const GridCoordinate &coord)
    : map_{map}, coord_{coord}
{
}

void DrillCommand::execute() const
{
    map_.drill(coord_);
}