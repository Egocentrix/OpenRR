#pragma once

#include <memory>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Command.hpp"
#include "Logging.hpp"
#include "MenuCommon.hpp"

class ContextMenu
{
public:
    ContextMenu(std::shared_ptr<sf::Font>);
    ~ContextMenu();

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
    Logger logger_{Logger::create("ContextMenu")};
};
