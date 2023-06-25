#include <iostream>

#include "Helpers.hpp"

FrameCounter::FrameCounter(float updateInterval)
    : updateIntervalSeconds{updateInterval}
{
}

void FrameCounter::tick()
{
    ++ticks;
    if (clock_.getElapsedTime().asSeconds() > updateIntervalSeconds)
    {
        std::cout << "FPS: " << int(ticks / updateIntervalSeconds) << "\tFrametime: " << 1000 * updateIntervalSeconds / ticks << " ms \n";
        clock_.restart();
        ticks = 0;
    }
    return;
}