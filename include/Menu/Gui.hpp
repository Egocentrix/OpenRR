#pragma once

#include "ContextMenu.hpp"
#include "ResourceManager.hpp"

class Gui
{
public:
    Gui(ResourceManager<sf::Font> &fonts);

    bool handleClickEvent(sf::Vector2i mouseposition);
    void draw(sf::RenderTarget &target);

    void createContextMenu(float x, float y, const std::string &title, std::vector<std::unique_ptr<Command>> actions);

private:
    ResourceManager<sf::Font> &fonts_;

    ContextMenu menu_;
};
