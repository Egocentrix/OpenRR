#pragma once

#include <stack>
#include <SFML/Graphics.hpp>

#include "GameStatePlay.hpp"
#include "Helpers.hpp"
#include "ResourceManager.hpp"

// Contains global game data. State-specific data is contained by the gamestate object.
class Game
{
public:
    Game();
    ~Game();

    void play();

    ResourceManager<sf::Texture> texureManager;
    ResourceManager<sf::Font> fontManager;
    sf::RenderWindow window;

private:
    void popState();

    sf::Clock clock{};
    FrameCounter fpscounter{3.f};
    std::stack<std::unique_ptr<GameState>> states{};
};
