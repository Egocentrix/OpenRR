#pragma once

#include <SFML/System/Clock.hpp>

#include "Logging.hpp"

class FrameCounter
{
public:
    FrameCounter() = default;
    FrameCounter(float updateIntervalSeconds, bool enableLogging);
    
    void tick();
    int getLastValue();

private:
    unsigned int ticks{0};
    sf::Clock clock_;
    float updateIntervalSeconds{3};
    bool enableLogging_{true};
    int lastvalue_;

    Logger logger_{Logger::create("FrameCounter")};
};
