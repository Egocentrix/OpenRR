#include "Game.hpp"

Game::Game()
    : window(sf::VideoMode(800, 600), "Hello, world!")
{
    state = new GameStatePlay(this);
}

Game::~Game()
{
    delete state;
}

void Game::play()
{
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        state->handleInput(dt);
        state->draw();
    }
}
