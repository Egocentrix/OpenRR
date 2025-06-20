#include <memory>

#include "CaveMap.hpp"
#include "MapCommands.hpp"
#include "GameStatePlay.hpp"
#include "Game.hpp"

GameStatePlay::GameStatePlay(Game *parent)
    : map{std::make_unique<CaveMap>(std::make_unique<FileMapLoader>("testmap.dat"))},
      menu{parent->fontManager.getResource("contextmenufont")},
      view{parent->window.getView()},
      guiview{parent->window.getDefaultView()}
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
    map->draw(game->window);

    game->window.setView(guiview);
    menu.draw(game->window);
}

void GameStatePlay::update()
{
    map->update(game->texureManager);
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

            // Do not scale the GUI size
            guiview.reset(sf::FloatRect(0, 0, e.size.width, e.size.height));
        }

        else if (e.type == sf::Event::MouseButtonPressed)
        {
            handleClickEvent(e);
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

void GameStatePlay::handleClickEvent(const sf::Event &e)
{
    auto mouseposition{sf::Mouse::getPosition(game->window)};
    auto worldposition{game->window.mapPixelToCoords(mouseposition, view)};
    GridCoordinate coord{static_cast<int>(worldposition.x), static_cast<int>(worldposition.y)};
    if (e.mouseButton.button == sf::Mouse::Left)
    {
        if (menu.visible)
        {
            menu.handleClickEvent(mouseposition);
            menu.visible = false;
        }
        else
        {
            for (auto &&c : map->availableCommands(coord))
            {
                if (c->describe() == "Drill")
                    c->execute();
            }
        }
    }
    else if (e.mouseButton.button == sf::Mouse::Right)
    {
        menu.setLocation(mouseposition.x, mouseposition.y);

        auto tilename = map->describeTile(coord);
        auto actions = map->availableCommands(coord);

        menu.setTitle(tilename);
        menu.setActions(actions);
        menu.visible = true;
    }
}
