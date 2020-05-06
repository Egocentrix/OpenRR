#pragma once

#include <SFML/Graphics.hpp>

#include "GameStatePlay.hpp"

class Game
{
private:
    sf::Clock clock;

    GameStatePlay *state;

public:
    Game();
    ~Game();

    sf::RenderWindow window;

    void play();
};
