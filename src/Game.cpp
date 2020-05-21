#include "Game.hpp"

Game::Game()
    : window(sf::VideoMode(800, 600), "Hello, world!")
{
    loadtexture("wad/rr0/World/WorldTextures/RockSplit/ROCK00.BMP", "floor");
    loadtexture("wad/rr0/World/WorldTextures/RockSplit/ROCK05.BMP", "wall");

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

void Game::loadtexture(const std::string &filename, const std::string &key)
{
    sf::Texture tex;
    tex.loadFromFile(filename);
    texmgr[key] = tex;
}
