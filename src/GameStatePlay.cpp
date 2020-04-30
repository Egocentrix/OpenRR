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
    map->draw(game->window);
    menu.draw(game->window);
    game->window.display();
}

void GameStatePlay::update()
{
    map->update();
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

        else if (e.type == sf::Event::Resized)
        {
            float ratio = static_cast<float>(e.size.width) / e.size.height;
            auto currentsize = view.getSize();
            view.setSize(currentsize.x, currentsize.x / ratio);
        }

        else if (e.type == sf::Event::MouseButtonPressed)
        {
            auto mouseposition{sf::Mouse::getPosition(game->window)};
            auto worldposition{game->window.mapPixelToCoords(mouseposition, view)};
            GridCoordinate coord{static_cast<int>(worldposition.x), static_cast<int>(worldposition.y)};
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                if (menu.visible)
                {
                    menu.visible = false;
                }
                else
                {
                    for (auto &&c : map->availableCommands(coord))
                    {
                        if (c->describe() == "Drill") c->execute();
                    }
                }
            }
            else if (e.mouseButton.button == sf::Mouse::Right)
            {
                menu.setLocation(mouseposition.x, mouseposition.y);
                menu.visible = true;

                std::cout << map->describeTile(coord) << ",\tavailable Commands:";
                for (auto &&c : map->availableCommands(coord))
                {
                    std::cout << " " << c->describe() << ",";
                }
                std::cout << std::endl;
            }
        }

        else if (e.type == sf::Event::MouseWheelScrolled)
        {
            const float zoomfactor = 1.2;
            if (e.mouseWheelScroll.delta > 0) // scroll up
            {
                view.zoom(1 / zoomfactor);
                zoomlevel *= zoomfactor;
            }
            else
            {
                view.zoom(zoomfactor);
                zoomlevel /= zoomfactor;
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        view.move(0, -10.f * dt / zoomlevel);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        view.move(0, 10.f * dt / zoomlevel);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        view.move(-10.f * dt / zoomlevel, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        view.move(10.f * dt / zoomlevel, 0);
    }
}