#include "Game.hpp"

Game::Game()
    : window(sf::VideoMode(800, 600), "Hello, world!")
{
    texmgr.loadTexture("floor", "wad/rr0/World/WorldTextures/RockSplit/ROCK00.BMP");
    texmgr.loadTexture("wall", "wad/rr0/World/WorldTextures/RockSplit/ROCK05.BMP");
    texmgr.loadTexture("wall_incorner", "wad/rr0/World/WorldTextures/RockSplit/ROCK55.BMP");
    texmgr.loadTexture("wall_outcorner", "wad/rr0/World/WorldTextures/RockSplit/ROCK35.BMP");

    states.push(new GameStatePlay(this));
}

Game::~Game()
{
    while (!states.empty())
    {
        popState();
    }
}

void Game::popState()
{
    delete states.top();
    states.pop();
}

void Game::play()
{
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        states.top()->handleInput(dt);
        states.top()->draw();
    }
}
