#include "WorkerSystem.hpp"

WorkerSystem::WorkerSystem(PathGenerator &pathGenerator)
    : pathGenerator_{pathGenerator}
{
    addWorker({5, 5});
    addWorker({5, 5});
    addWorker({5, 5});
}

void WorkerSystem::addWorker(sf::Vector2f position)
{
    workers_.emplace_back(position);
}

void WorkerSystem::addTask(Task task)
{
    taskQueue_.push(std::move(task));
}

void WorkerSystem::update(float dt)
{
    dispatchTasks();
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

void WorkerSystem::dispatchTasks()
{
    if (!taskQueue_.empty())
    {
        auto it = std::find_if_not(workers_.begin(), workers_.end(), [](Worker &w)
                                   { return w.isBusy(); });
        if (it != workers_.end())
        {
            auto path = pathGenerator_.findRoute(it->getCurrentPosition(), taskQueue_.front().location);
            it->assignTask(std::move(taskQueue_.front()), path);
            taskQueue_.pop();
        }
    }
}