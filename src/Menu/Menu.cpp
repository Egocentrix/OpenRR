#include "Menu.hpp"

Menu::Menu(/* args */)
{
    addItem("Test1");
    addItem("test2");
    setLocation(0, 0);
    visible = false;
}

Menu::~Menu()
{
}

void Menu::addItem(const std::string &name)
{
    items.push_back(name);
}

void Menu::setLocation(float x, float y)
{
    x_ = x;
    y_ = y;
}

void Menu::setActions(std::vector<std::unique_ptr<Command>>& actionlist)
{
    items.clear();
    for (auto&& action : actionlist)
    {
        addItem(action->describe());
    }
}

void Menu::draw(sf::RenderTarget &target)
{
    if (!visible)
    {
        return;
    }

    sf::RectangleShape border(sf::Vector2f(200, 50 * items.size()));
    border.setFillColor(sf::Color(150, 150, 150));
    border.setPosition(x_, y_);
    target.draw(border);
}
