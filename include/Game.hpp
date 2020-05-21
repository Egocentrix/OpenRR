#pragma once

#include <stack>
#include <map>
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

    std::map<std::string, sf::Texture> texmgr;
    void loadtexture(const std::string &filename, const std::string &key);

    sf::RenderWindow window;

    void play();
};
