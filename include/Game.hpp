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

    void LoadTextures();
    void LoadFonts();

    void handleInput(float dt);
    void update(float dt);
    void draw();

    sf::Clock clock{};
    FrameCounter fpscounter{1.f, false};
    sf::Text fpsdisplay;
    std::stack<std::unique_ptr<GameState>> states{};
};
