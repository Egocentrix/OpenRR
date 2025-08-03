#pragma once

#include <functional>
#include <unordered_map>

#include <SFML/Window/Keyboard.hpp>

class KeyboardEventHandler
{
public:
    void registerEvent(sf::Keyboard::Key key, std::function<void()> action);
    void handleKeyEvents(sf::Keyboard::Key key);

private:
    std::unordered_map<sf::Keyboard::Key, std::function<void()>> keyboardActions_; 
};