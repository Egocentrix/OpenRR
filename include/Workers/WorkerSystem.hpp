#pragma once

#include <vector>

#include "Worker.hpp"

class WorkerSystem
{
public:
    WorkerSystem();

    void addWorker(sf::Vector2f position);
    void addDestination(sf::Vector2f destination);

    void update(float dt);
    void draw(sf::RenderTarget &target);

private:
    std::vector<Worker> workers_;
};