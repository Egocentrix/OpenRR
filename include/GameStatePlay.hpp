#pragma once

#include "CaveMap.hpp"
#include "GameState.hpp"

// The main state where the game is played
class GameStatePlay : public GameState
{
public:
    GameStatePlay(Game *parent);
    ~GameStatePlay();

    virtual void draw() override;
    virtual void handleInput(float dt) override;

private:
    CaveMap map;
    sf::View view;
};
