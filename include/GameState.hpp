#pragma once

class Game;

// Base class for game states (abstract)
class GameState
{
public:
    // Abstract base destructor requires definition for some reason
    virtual ~GameState() { } 
    
    Game* game;

    virtual void handleInput(float dt) = 0;
    virtual void draw() = 0;

};