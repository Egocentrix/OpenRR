#include <SFML/Window/Keyboard.hpp>

#include "Camera.hpp"

void Camera::zoomIn()
{
    view_.zoom(1 / zoomFactor);
    zoomlevel /= zoomFactor;
}

void Camera::zoomOut()
{
    view_.zoom(zoomFactor);
    zoomlevel *= zoomFactor;
}

void Camera::reset(sf::Vector2f size, sf::Vector2f center)
{
    view_.setCenter(center);
    view_.setSize(size);
}

void Camera::resize(float width, float height)
{
    float ratio = width / height;
    auto currentsize = view_.getSize();
    view_.setSize(currentsize.x, currentsize.x / ratio);
}

void Camera::update(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        view_.move(0, -1 * moveSpeed * dt * zoomlevel);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        view_.move(0, moveSpeed * dt * zoomlevel);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        view_.move(-1 * moveSpeed * dt * zoomlevel, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        view_.move(moveSpeed * dt * zoomlevel, 0);
    }
}

const sf::View &Camera::getView() const
{
    return view_;
}
