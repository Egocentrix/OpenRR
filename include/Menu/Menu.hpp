#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Menu
{
public:
    Menu(/* args */);
    ~Menu();

    bool visible;

    void addItem(const std::string &name);
    void setLocation(float x, float y);

    void draw(sf::RenderTarget &target);

private:
    std::vector<std::string> items;
    float x_, y_;
};
