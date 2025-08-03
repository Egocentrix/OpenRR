#include "KeyboardEventHandler.hpp"

void KeyboardEventHandler::handleKeyEvents(sf::Keyboard::Key key)
{
    if(keyboardActions_.contains(key))
    {
        auto action = keyboardActions_.at(key);
        action();
    }
}

void KeyboardEventHandler::registerEvent(sf::Keyboard::Key key, std::function<void()> action)
{
    keyboardActions_[key] = action;
}
