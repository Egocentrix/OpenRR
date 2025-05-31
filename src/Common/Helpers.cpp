#include <format>

#include "Helpers.hpp"
#include "Logging.hpp"

FrameCounter::FrameCounter(float updateInterval)
    : updateIntervalSeconds{updateInterval}
{
}

void FrameCounter::tick()
{
    ++ticks;
    if (clock_.getElapsedTime().asSeconds() > updateIntervalSeconds)
    {
        auto fps = int(ticks / updateIntervalSeconds);
        auto frametimeMilliseconds = 1000 * updateIntervalSeconds / ticks;

        Logger::Log("FrameCounter", std::format("FPS: {}\tFrametime: {} ms", fps, frametimeMilliseconds));
        
        clock_.restart();
        ticks = 0;
    }
    return;
}