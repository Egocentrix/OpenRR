#pragma once

class Game;

class GameState
{
public:
    virtual ~GameState() { }
    
    Game* game;

    virtual void handleInput(float dt) = 0;
    virtual void draw() = 0;

};