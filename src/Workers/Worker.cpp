#include <cmath>

#include "Worker.hpp"

Worker::Worker()
{
}

void Worker::setTarget(sf::Vector2f position)
{
    targetPositon_ = position;
}

void Worker::update(float dt)
{
    auto dir = targetPositon_ - currentPosition_;
    auto dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (dist < 0.1)
    {
        return;
    }
    
    dir = dir / dist;
    currentPosition_ = currentPosition_ + (dir * dt);
}

void Worker::draw(sf::RenderTarget &target)
{
    sf::RectangleShape shape{{0.1f, 0.1f}};
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(currentPosition_);

    target.draw(shape);
}
