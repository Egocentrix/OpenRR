#include <cmath>

#include "Worker.hpp"

Worker::Worker()
{
}

void Worker::update(float dt)
{
    auto dir = targetPositon_ - currentPosition_;
    dir = dir / std::sqrt(dir.x * dir.x + dir.y * dir.y);
    currentPosition_ = currentPosition_ + (dir * dt);
}

void Worker::draw(sf::RenderTarget &target)
{
    sf::RectangleShape shape{{0.1f, 0.1f}};
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(currentPosition_);

    target.draw(shape);
}
