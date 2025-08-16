#pragma once

#include <queue>
#include <SFML/Graphics.hpp>

class Worker
{
public:
    Worker(sf::Vector2f initialPosition);

    void addDestination(sf::Vector2f position);

    bool isBusy();
    sf::Vector2f getCurrentPosition();

    void update(float dt);
    void draw(sf::RenderTarget &target);

private:
    sf::Vector2f currentPosition_;
    std::queue<sf::Vector2f> path_;
};
