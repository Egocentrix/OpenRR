#include "Menu.hpp"

Menu::Menu(const sf::Font& font)
: font_{font}
{
    setLocation(0, 0);
    visible = false;
}

Menu::~Menu()
{
}

void Menu::addItem(const std::string &name, std::unique_ptr<Command> action)
{
    items_.push_back(MenuItem(name, std::move(action)));
}

void Menu::setLocation(float x, float y)
{
    x_ = x;
    y_ = y;
}

void Menu::setActions(std::vector<std::unique_ptr<Command>>& actionlist)
{
    items_.clear();
    for (auto&& action : actionlist)
    {
        const std::string name = action->describe();
        addItem(name, std::move(action));
    }
}

void Menu::setTitle(const std::string &title)
{
    title_ = title;
}

void Menu::draw(sf::RenderTarget &target)
{
    if (!visible)
    {
        return;
    }

    sf::RectangleShape border(sf::Vector2f(200, 50 * (items_.size() + 1)));
    border.setFillColor(sf::Color(150, 150, 150));
    border.setPosition(x_, y_);
    target.draw(border);

    sf::Text title(title_, font_, 30);
    title.setPosition(x_ + 5, y_);
    target.draw(title);

    sf::Text itemlabel("", font_, 30);
    for (size_t i = 0; i < items_.size(); ++i)
    {
        itemlabel.setString(items_[i].title);
        itemlabel.setPosition(x_ + 10, y_ + (50*(i+1)));
        target.draw(itemlabel);
    }
}
