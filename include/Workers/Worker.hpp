#pragma once

#include <SFML/Graphics.hpp>

class Worker
{
public:
    Worker(/* args */);

    void update(float dt);
    void draw(sf::RenderTarget &target);

private:
    sf::Vector2f currentPosition_{5, 5};
    sf::Vector2f targetPositon_{0, 0};
};
