#include <memory>

#include "CaveMap.hpp"
#include "MapCommands.hpp"
#include "GameStatePlay.hpp"
#include "Game.hpp"

GameStatePlay::GameStatePlay(Game *parent)
    : map{std::make_unique<CaveMap>(std::make_unique<FileMapLoader>("testmap.dat"))},
      menu{parent->fontManager.getResource("contextmenufont")},
      guiview{parent->window.getDefaultView()}
{
    this->game = parent;
    auto center = map->getCenter();
    camera.reset(sf::Vector2f(15, 15), sf::Vector2f(center.x, center.y));

    keyboardEventHandler.registerEvent(sf::Keyboard::Escape, [this]()
                                       { game->window.close(); });
}

GameStatePlay::~GameStatePlay()
{
}

void GameStatePlay::draw()
{
    game->window.setView(camera.getView());
    map->draw(game->window);
    worker.draw(game->window);

    game->window.setView(guiview);
    menu.draw(game->window);
}

void GameStatePlay::update(float dt)
{
    camera.update(dt);
    map->update(game->texureManager);
    worker.update(dt);
}

void GameStatePlay::handleInput(float)
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
            camera.resize(e.size.width, e.size.height);

            // Do not scale the GUI size
            guiview.reset(sf::FloatRect(0, 0, e.size.width, e.size.height));
        }

        else if (e.type == sf::Event::MouseButtonPressed)
        {
            handleClickEvent(e);
        }

        else if (e.type == sf::Event::MouseWheelScrolled)
        {
            e.mouseWheelScroll.delta > 0 ? camera.zoomIn() : camera.zoomOut();
        }

        else if (e.type == sf::Event::KeyPressed)
        {
            keyboardEventHandler.handleKeyEvents(e.key.code);
        }
    }
}

void GameStatePlay::handleClickEvent(const sf::Event &e)
{
    auto mouseposition{sf::Mouse::getPosition(game->window)};
    auto worldposition{game->window.mapPixelToCoords(mouseposition, camera.getView())};
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
            for (auto &&c : map->getAvailableCommands(coord))
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
        auto actions = map->getAvailableCommands(coord);

        menu.setTitle(tilename);
        menu.setActions(actions);
        menu.visible = true;

        // For testing
        worker.addDestination({worldposition.x, worldposition.y});
    }
}
