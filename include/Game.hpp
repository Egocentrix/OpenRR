#pragma once

#include <SFML/Graphics.hpp>

#include "CaveMap.hpp"

class Game
{
private:
    CaveMap map;

    sf::RenderWindow window;
    sf::View view;
    sf::Clock clock;

    void draw();
    void handleInput(float dt);

public:
    Game();
    ~Game();

    void play();
};
