#pragma once

#include <vector>
#include <queue>

#include "PathGenerator.hpp"
#include "Task.hpp"
#include "Worker.hpp"

class WorkerSystem
{
public:
    WorkerSystem(PathGenerator& pathGenerator);

    void addWorker(sf::Vector2f position);
    void addTask(Task task);

    void update(float dt);
    void draw(sf::RenderTarget &target);

private:
    void dispatchTasks();

    std::vector<Worker> workers_;
    std::queue<Task> taskQueue_;

    PathGenerator& pathGenerator_;
};