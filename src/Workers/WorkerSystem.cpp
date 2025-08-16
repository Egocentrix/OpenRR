#include "WorkerSystem.hpp"

WorkerSystem::WorkerSystem(/* args */)
{
    addWorker({0, 0});
    addWorker({0, 0});
    addWorker({0, 0});
}

void WorkerSystem::addWorker(sf::Vector2f position)
{
    workers_.emplace_back(position);
}

void WorkerSystem::addDestination(sf::Vector2f position)
{
    destinations_.push(position);
}

void WorkerSystem::update(float dt)
{
    for (auto &&worker : workers_)
    {
        worker.update(dt);
    }

    if (!destinations_.empty())
    {
        auto it = std::find_if_not(workers_.begin(), workers_.end(), [](Worker &w)
                                   { return w.isBusy(); });
        if (it != workers_.end())
        {
            it->addDestination(destinations_.front());
            destinations_.pop();
        }
    }
}

void WorkerSystem::draw(sf::RenderTarget &target)
{
    for (auto &&worker : workers_)
    {
        worker.draw(target);
    }
}
