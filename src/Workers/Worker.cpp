#include <cmath>

#include "Worker.hpp"

Worker::Worker(sf::Vector2f initialPosition)
: currentPosition_{initialPosition}
{
}

void Worker::addDestination(sf::Vector2f position)
{
    path_.push(position);
}

bool Worker::isBusy()
{
    return !path_.empty();
}

sf::Vector2f Worker::getCurrentPosition()
{
    return currentPosition_;
}

void Worker::update(float dt)
{
    if (path_.empty())
    {
        return;
    }
    
    auto dir = path_.front() - currentPosition_;
    auto dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (dist < 0.1)
    {
        path_.pop();
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
