#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "Command.hpp"

struct MenuStyle
{
    int MenuWidth{180};
    int MenuItemHeight{40};

    int fontSize{25};
    std::shared_ptr<sf::Font> font_;
    sf::Color backgroundColor{sf::Color(100, 100, 100)};
    sf::Color titleTextColor{sf::Color::Blue};
    sf::Color itemTextColor{sf::Color::White};
};

class MenuItem
{
public:
    MenuItem(std::string itemtitle, std::unique_ptr<Command> itemaction)
        : title{itemtitle}, action{std::move(itemaction)}
    {
    }

    std::string title{};
    std::unique_ptr<Command> action{};
};