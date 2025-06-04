#include <format>

#include "Helpers.hpp"

FrameCounter::FrameCounter(float updateInterval, bool enableLogging)
    : updateIntervalSeconds{updateInterval},
      enableLogging_{enableLogging}
{
}

void FrameCounter::tick()
{
    ++ticks;
    auto time = clock_.getElapsedTime();
    if (time.asSeconds() > updateIntervalSeconds)
    {
        auto fps = int(ticks / time.asSeconds());
        auto frametimeMilliseconds = time.asMilliseconds() / ticks;

        if (enableLogging_)
        {
            logger_.Log(std::format("FPS: {}\tFrametime: {} ms", fps, frametimeMilliseconds));
        }

        clock_.restart();
        ticks = 0;
        lastvalue_ = fps;
    }
    return;
}

int FrameCounter::getLastValue()
{
    return lastvalue_;
}
