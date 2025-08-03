#pragma once

#include <SFML/Graphics/View.hpp>

class Camera
{
public:
    void zoomIn();
    void zoomOut();
    void reset(sf::Vector2f size, sf::Vector2f center);
    void resize(float width, float height);

    void update(float dt);

    const sf::View& getView() const;

private:
    sf::View view_;
    float zoomlevel{1};

    static constexpr float zoomFactor{1.2};
    static constexpr float moveSpeed{10.0};
};
