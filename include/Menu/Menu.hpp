#pragma once

#include <memory>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Command.hpp"

struct MenuStyle
{
    int MenuWidth{180};
    int MenuItemHeight{40};

    int fontSize{25};
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

class Menu
{
public:
    Menu(std::shared_ptr<sf::Font>);
    ~Menu();

    bool visible;

    void addItem(const std::string &name, std::unique_ptr<Command> action);
    void setLocation(float x, float y);
    void setActions(std::vector<std::unique_ptr<Command>> &actionlist);
    void setTitle(const std::string &title);
    void setStyle(const MenuStyle &style);

    bool handleClickEvent(sf::Vector2i mouseposition);
    void draw(sf::RenderTarget &target);

private:
    std::string title_;
    std::vector<MenuItem> items_;
    float x_, y_;
    std::shared_ptr<sf::Font> font_;

    MenuStyle style_;
};
