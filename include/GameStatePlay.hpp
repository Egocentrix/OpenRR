#pragma once

#include "CaveMap.hpp"
#include "GameState.hpp"

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
