#pragma once

#include <SFML/System/Clock.hpp>

class FrameCounter
{
public:
    void tick();

private:
    unsigned int ticks{0};
    sf::Clock clock_;
};
