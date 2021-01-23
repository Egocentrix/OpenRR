#pragma once

#include <SFML/System/Clock.hpp>

class FrameCounter
{
public:
    FrameCounter() = default;
    FrameCounter(float updateIntervalSeconds);
    void tick();

private:
    unsigned int ticks{0};
    sf::Clock clock_;
    float updateIntervalSeconds{3};
};
