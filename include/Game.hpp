#pragma once

#include <stack>
#include <SFML/Graphics.hpp>

#include "GameStatePlay.hpp"
#include "Helpers.hpp"
#include "TextureManager.hpp"

// Contains global game data. State-specific data is contained by the gamestate object.
class Game
{
public:
    Game();
    ~Game();

    void play();

    TextureManager texmgr{};
    sf::RenderWindow window;

private:
    void popState();

    sf::Clock clock{};
    FrameCounter fpscounter;
    std::stack<std::unique_ptr<GameState>> states{};
};
