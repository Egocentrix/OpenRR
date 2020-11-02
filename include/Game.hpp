#pragma once

#include <stack>
#include <SFML/Graphics.hpp>

#include "GameStatePlay.hpp"
#include "TextureManager.hpp"

// Contains global game data. State-specific data is contained by the gamestate object.
class Game
{
private:
    sf::Clock clock;

    std::stack<std::unique_ptr<GameState>> states;

    void popState();

public:
    Game();
    ~Game();

    TextureManager texmgr;
    sf::RenderWindow window;

    void play();
};
