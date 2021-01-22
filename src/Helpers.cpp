#include <iostream>

#include "Helpers.hpp"

void FrameCounter::tick()
{
    ++ticks;
    if (clock_.getElapsedTime().asSeconds() > 2)
    {
        std::cout << "FPS: " << ticks << "\tFrametime: " << 2000.f / ticks << " ms \n";
        clock_.restart();
        ticks = 0;
    }
    return;
}