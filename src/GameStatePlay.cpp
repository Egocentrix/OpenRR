#include "GameStatePlay.hpp"
#include "Game.hpp"

GameStatePlay::GameStatePlay(Game *parent)
    : map(10, 10),
      view(sf::FloatRect(0, 0, 800, 600))
{
    this->game = parent;
    map.load("testmap.dat");
}

GameStatePlay::~GameStatePlay()
{
    map.save("testmap.dat");
}

void GameStatePlay::draw()
{
    game->window.setView(view);
    game->window.clear(sf::Color::Black);
    map.draw(game->window, game->texmgr);
    game->window.display();
}

void GameStatePlay::handleInput(float dt)
{
    sf::Event e;
    while (game->window.pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
        {
            game->window.close();
        }

        if (e.type == sf::Event::Resized)
        {
            view.setSize(e.size.width, e.size.height);
        }

        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f tile = game->window.mapPixelToCoords(sf::Mouse::getPosition(game->window)) / 50.f;
                if (map.getTile(tile.x, tile.y).discovered)
                {
                    map.drill(tile.x, tile.y);
                }
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        view.move(0, -100.f * dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        view.move(0, 100.f * dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        view.move(-100.f * dt, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        view.move(100.f * dt, 0);
    }
}