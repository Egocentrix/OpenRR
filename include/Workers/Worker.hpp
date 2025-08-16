#pragma once

#include <queue>
#include <SFML/Graphics.hpp>

class Worker
{
public:
    Worker(/* args */);

    void addDestination(sf::Vector2f position);

    void update(float dt);
    void draw(sf::RenderTarget &target);

private:
    sf::Vector2f currentPosition_{5, 5};
    std::queue<sf::Vector2f> path_;
};
