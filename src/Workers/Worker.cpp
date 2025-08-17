#include <cmath>

#include "Worker.hpp"

Worker::Worker(sf::Vector2f initialPosition)
    : currentPosition_{initialPosition}
{
}

void Worker::assignTask(Task task, const std::vector<sf::Vector2f> &path)
{
    currentTask_ = std::move(task);
    for (auto &&node : path)
    {
        path_.push(node);
    }
}

bool Worker::isBusy()
{
    return currentTask_.has_value();
}

sf::Vector2f Worker::getCurrentPosition()
{
    return currentPosition_;
}

void Worker::update(float dt)
{
    if (path_.empty())
    {
        if (currentTask_)
        {
            if (currentTask_->action)
            {
                currentTask_->action->execute();
            }
            currentTask_ = {};
        }

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
