#pragma once

#include <stack>
#include <SFML/Graphics.hpp>

#include "GameStatePlay.hpp"

// Contains global game data. State-specific data is contained by the gamestate object.
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
