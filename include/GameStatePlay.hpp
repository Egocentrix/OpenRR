#pragma once

#include <memory>

#include "CaveMapInterface.hpp"
#include "GameState.hpp"

// The main state where the game is played
class GameStatePlay : public GameState
{
public:
    GameStatePlay(Game *parent);
    ~GameStatePlay();

    virtual void draw() override;
    virtual void update() override;
    virtual void handleInput(float dt) override;

private:
    std::unique_ptr<CaveMapInterface> map;
    sf::View view;
    float zoomlevel{1};
};
