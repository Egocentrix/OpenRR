#include "Game.hpp"

Game::Game()
    : window{sf::VideoMode(800, 600), "Hello, world!"}
{    
    LoadTextures();
    LoadFonts();    
    
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

void Game::LoadTextures()
{
    texureManager.registerResource("floor", "wad/rr0/World/WorldTextures/RockSplit/ROCK00.BMP");
    texureManager.registerResource("wall_incorner", "wad/rr0/World/WorldTextures/RockSplit/ROCK35.BMP");
    texureManager.registerResource("wall_outcorner", "wad/rr0/World/WorldTextures/RockSplit/ROCK55.BMP");
    texureManager.registerResource("wall", "wad/rr0/World/WorldTextures/RockSplit/ROCK05.BMP");
    texureManager.registerResource("wall_split", "wad/rr0/World/WorldTextures/RockSplit/ROCK77.BMP");
}

void Game::LoadFonts()
{
    fontManager.registerResource("contextmenufont", "OpenSans-Regular.ttf");
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
