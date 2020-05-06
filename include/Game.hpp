#pragma once

#include <stack>
#include <SFML/Graphics.hpp>

#include "GameStatePlay.hpp"

class Game
{
private:
    sf::Clock clock;

    std::stack<GameState *> states;

    void popState();

public:
    Game();
    ~Game();

    sf::RenderWindow window;

    void play();
};
