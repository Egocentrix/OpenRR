#include "Gui.hpp"

Gui::Gui(ResourceManager<sf::Font> &fonts)
    : fonts_{fonts},
      menu_{fonts.getResource("contextmenufont")}
{
}

bool Gui::handleClickEvent(sf::Vector2i mouseposition)
{
    bool handled = false;
    if (menu_.visible)
    {
        menu_.handleClickEvent(mouseposition);
        menu_.visible = false;
        handled = true;
    }

    return handled;
}

void Gui::draw(sf::RenderTarget &target)
{
    menu_.draw(target);
}

void Gui::createContextMenu(float x, float y, const std::string &title, std::vector<std::unique_ptr<Command>> actions)
{
    menu_.setLocation(x, y);
    menu_.setTitle(title);
    menu_.setActions(actions);
    menu_.visible = true;
}
