#include "Game.hpp"

Game::Game()
    : window(sf::VideoMode(800, 600), "Hello, world!"),
      view(sf::FloatRect(0, 0, 800, 600)),
      map(10, 10)
{
}

Game::~Game()
{
}

void Game::play()
{
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        handleInput(dt);
        draw();
    }
}

void Game::draw()
{
    window.setView(view);
    window.clear(sf::Color::Black);
    map.draw(window);
    window.display();
}

void Game::handleInput(float dt)
{
    sf::Event e;
    while (window.pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
        {
            window.close();
        }

        if (e.type == sf::Event::Resized)
        {
            view.setSize(e.size.width, e.size.height);
        }

        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f tile = window.mapPixelToCoords(sf::Mouse::getPosition(window)) / 50.f;
                if (map.isDiscovered(tile.x, tile.y))
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