#include <iostream>
#include <memory>

#include "CaveMap.hpp"
#include "MapCommands.hpp"
#include "GameStatePlay.hpp"
#include "Game.hpp"

GameStatePlay::GameStatePlay(Game *parent)
    : map{std::make_unique<CaveMap>(
          std::make_unique<FileMapLoader>("testmap.dat"),
          *(parent->texmgr))},
      view{parent->window.getView()}
{
    this->game = parent;
    GridCoordinate center = map->getCenter();
    view.setCenter(center.x, center.y);
    view.setSize(15, 15);
}

GameStatePlay::~GameStatePlay()
{
}

void GameStatePlay::draw()
{
    game->window.setView(view);
    game->window.clear(sf::Color::Black);
    map->update();
    map->draw(game->window);
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
            float ratio = static_cast<float>(e.size.width) / e.size.height;
            auto currentsize = view.getSize();
            view.setSize(currentsize.x, currentsize.x / ratio);
        }

        if (e.type == sf::Event::MouseButtonPressed &&
            e.mouseButton.button == sf::Mouse::Left)
        {
            auto mouseposition{sf::Mouse::getPosition(game->window)};
            auto worldposition{game->window.mapPixelToCoords(mouseposition, view)};
            GridCoordinate coord{static_cast<int>(worldposition.x), static_cast<int>(worldposition.y)};

            std::cout << map->describeTile(coord) << ",\tavailable Commands:";
            for (auto &&c : map->availableCommands(coord))
            {
                std::cout << " " << c->describe() << ",";
                if (c->describe() == "Drill")
                {
                    c->execute();
                }
            }
            std::cout << std::endl;
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