#include "Game.hpp"

Game::Game()
    : window(sf::VideoMode(800, 600), "Hello, world!")
{
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
