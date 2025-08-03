#pragma once

#include <memory>

#include "CaveMapInterface.hpp"
#include "GameState.hpp"
#include "KeyboardEventHandler.hpp"
#include "Menu.hpp"

// The main state where the game is played
class GameStatePlay : public GameState
{
public:
    GameStatePlay(Game *parent);
    ~GameStatePlay();

    virtual void draw() override;
    virtual void update() override;
    virtual void handleInput(float dt) override;

private:
    std::unique_ptr<CaveMapInterface> map;
    Menu menu;
    sf::View view;
    sf::View guiview;
    float zoomlevel{1};
    KeyboardEventHandler keyboardEventHandler;

    void handleClickEvent(const sf::Event &e);
};
