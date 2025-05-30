#pragma once

#include <memory>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Command.hpp"

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

class Menu
{
public:
    Menu(const sf::Font&);
    ~Menu();

    bool visible;

    void addItem(const std::string &name, std::unique_ptr<Command> action);
    void setLocation(float x, float y);
    void setActions(std::vector<std::unique_ptr<Command>>& actionlist);
    void setTitle(const std::string &title);

    void draw(sf::RenderTarget &target);

private:
    std::string title_;
    std::vector<MenuItem> items_;
    float x_, y_;
    const sf::Font& font_;
};
