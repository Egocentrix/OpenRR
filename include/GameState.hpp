#pragma once

class Game;

class GameState
{
public:
    Game* game;

    virtual void handleInput(float dt) = 0;
    virtual void draw() = 0;

};
