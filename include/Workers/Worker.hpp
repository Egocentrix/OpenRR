#pragma once

#include <optional>
#include <queue>
#include <SFML/Graphics.hpp>

#include <Task.hpp>

class Worker
{
public:
    Worker(sf::Vector2f initialPosition);

    void assignTask(Task task, const std::vector<sf::Vector2f>& path);

    bool isBusy();
    sf::Vector2f getCurrentPosition();

    void update(float dt);
    void draw(sf::RenderTarget &target);

private:
    std::optional<Task> currentTask_;
    sf::Vector2f currentPosition_;
    std::queue<sf::Vector2f> path_;
};
