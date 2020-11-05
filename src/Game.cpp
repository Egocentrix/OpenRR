#include "Game.hpp"

Game::Game()
    : window(sf::VideoMode(800, 600), "Hello, world!")
{
    texmgr.registerTexture("floor", "wad/rr0/World/WorldTextures/RockSplit/ROCK00.BMP");
    texmgr.registerTexture("wall_incorner", "wad/rr0/World/WorldTextures/RockSplit/ROCK55.BMP");
    texmgr.registerTexture("wall_outcorner", "wad/rr0/World/WorldTextures/RockSplit/ROCK35.BMP");
    texmgr.registerTexture("wall", "wad/rr0/World/WorldTextures/RockSplit/ROCK05.BMP");
    
    states.push(std::make_unique<GameStatePlay>(this));
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
