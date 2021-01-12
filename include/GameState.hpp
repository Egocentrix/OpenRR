#pragma once

class Game;

// Base class for game states (abstract)
class GameState
{
public:
    virtual void handleInput(float dt) = 0;
    virtual void draw() = 0;

    virtual ~GameState() = default;

    Game *game;
};