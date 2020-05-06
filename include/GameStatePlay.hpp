#pragma once

#include "CaveMap.hpp"
#include "GameState.hpp"

// The main state where the game is played
class GameStatePlay : public GameState
{
private:
    CaveMap map;

    sf::View view;

public:
    GameStatePlay(Game *game);
    ~GameStatePlay();

    virtual void draw();
    virtual void handleInput(float dt);
};
