#include "CaveMapLoader.hpp"
#include "MapCommands.hpp"
#include "GameStatePlay.hpp"
#include "Game.hpp"

GameStatePlay::GameStatePlay(Game *parent)
    : map{std::make_unique<FileMapLoader>("testmap.dat"), *(parent->texmgr)},
      view{parent->window.getView()}
{
    this->game = parent;
}

GameStatePlay::~GameStatePlay()
{
}

void GameStatePlay::draw()
{
    game->window.setView(view);
    game->window.clear(sf::Color::Black);
    map.draw(game->window);
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

        if (e.type == sf::Event::MouseButtonPressed &&
            e.mouseButton.button == sf::Mouse::Left)
        {
            auto mouseposition{sf::Mouse::getPosition(game->window)};
            auto worldposition{game->window.mapPixelToCoords(mouseposition, view) / CaveMap::TILESIZE};
            GridCoordinate coord{static_cast<int>(worldposition.x), static_cast<int>(worldposition.y)};
            if (map.isVisible(coord))
            {
                CaveMapController::executeCommand(DrillCommand(map, coord));
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