#pragma once

#include "CaveMap.hpp"
#include "GameState.hpp"

// The main state where the game is played
class GameStatePlay : public GameState
{
public:
    GameStatePlay(Game *parent);
    ~GameStatePlay();

    virtual void draw();
    virtual void handleInput(float dt);

private:
    CaveMap map;
    sf::View view;
};
