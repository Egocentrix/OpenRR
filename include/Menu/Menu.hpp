#pragma once

#include <memory>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Command.hpp"

class Menu
{
public:
    Menu();
    ~Menu();

    bool visible;

    void addItem(const std::string &name);
    void setLocation(float x, float y);
    void setActions(std::vector<std::unique_ptr<Command>>& actionlist);

    void draw(sf::RenderTarget &target);

private:
    std::vector<std::string> items;
    float x_, y_;
};
