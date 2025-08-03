#pragma once

#include <memory>

#include "Camera.hpp"
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
    virtual void update(float dt) override;
    virtual void handleInput(float dt) override;

private:
    std::unique_ptr<CaveMapInterface> map;
    Camera camera;
    Menu menu;
    sf::View guiview;
    KeyboardEventHandler keyboardEventHandler;

    void handleClickEvent(const sf::Event &e);
};
