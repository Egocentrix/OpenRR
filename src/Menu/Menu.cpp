#include "Menu.hpp"

#include "Logging.hpp"

Menu::Menu(std::shared_ptr<sf::Font> font)
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

void Menu::setStyle(const MenuStyle &style)
{
    style_ = style;
}

bool Menu::handleClickEvent(sf::Vector2i mouseposition)
{
    auto localCoordinates = mouseposition - sf::Vector2i(x_, y_);
    int itemcount = items_.size();
    if (localCoordinates.x < 0 || 
        localCoordinates.y < 0 ||
        localCoordinates.x > style_.MenuWidth || 
        localCoordinates.y > style_.MenuItemHeight * (itemcount + 1))
    {
        return false;
    }
    
    auto itemindex = localCoordinates.y / style_.MenuItemHeight - 1;
    if (itemindex < 0 || itemindex >= itemcount)
    {
        return false;
    }
    
    Logger::Log("ContextMenu", "Selected item: " + items_[itemindex].title);
    items_[itemindex].action->execute();

    return true;
}

void Menu::draw(sf::RenderTarget &target)
{
    if (!visible)
    {
        return;
    }

    sf::RectangleShape border(sf::Vector2f(style_.MenuWidth, style_.MenuItemHeight * (items_.size() + 1)));
    border.setFillColor(style_.backgroundColor);
    border.setPosition(x_, y_);
    target.draw(border);

    sf::Text title(title_, *font_, style_.fontSize);
    title.setFillColor(style_.titleTextColor);
    title.setPosition(x_ + 5, y_ + 5);
    target.draw(title);

    sf::Text itemlabel("", *font_, style_.fontSize);
    itemlabel.setFillColor(style_.itemTextColor);
    for (size_t i = 0; i < items_.size(); ++i)
    {
        itemlabel.setString(items_[i].title);
        itemlabel.setPosition(x_ + 20, y_ + 5 + (style_.MenuItemHeight * (i+1)));
        target.draw(itemlabel);
    }
}
