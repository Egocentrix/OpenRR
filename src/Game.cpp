#include "Game.hpp"
#include "TextureManager.hpp"

Game::Game()
    : texmgr{std::make_unique<TextureManager>()},
      window{sf::VideoMode(800, 600), "Hello, world!"}
{    
    texmgr->registerResource("floor", "wad/rr0/World/WorldTextures/RockSplit/ROCK00.BMP");
    texmgr->registerResource("wall_incorner", "wad/rr0/World/WorldTextures/RockSplit/ROCK35.BMP");
    texmgr->registerResource("wall_outcorner", "wad/rr0/World/WorldTextures/RockSplit/ROCK55.BMP");
    texmgr->registerResource("wall", "wad/rr0/World/WorldTextures/RockSplit/ROCK05.BMP");
    
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
        fpscounter.tick();

        states.top()->handleInput(dt);
        states.top()->update();
        states.top()->draw();
    }
}
