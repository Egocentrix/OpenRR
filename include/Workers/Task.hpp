#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "Command.hpp"

struct Task
{
    Task(const sf::Vector2f &location_, std::unique_ptr<Command> action_)
    : location{location_}, action{std::move(action_)}
    {
    }

    sf::Vector2f location;
    std::unique_ptr<Command> action;
};
