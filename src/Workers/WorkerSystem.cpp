#include "WorkerSystem.hpp"

WorkerSystem::WorkerSystem(/* args */)
{
    addWorker({0,0});
    addWorker({0,0});
    addWorker({0,0});
}

void WorkerSystem::addWorker(sf::Vector2f position)
{
    workers_.emplace_back(position);
}

void WorkerSystem::addDestination(sf::Vector2f position)
{
    static size_t index = 0;
    workers_[index].addDestination(position);
    index = (index + 1) % workers_.size();
}

void WorkerSystem::update(float dt)
{
    for (auto &&worker : workers_)
    {
        worker.update(dt);
    }
}

void WorkerSystem::draw(sf::RenderTarget &target)
{
    for (auto &&worker : workers_)
    {
        worker.draw(target);
    }
}

