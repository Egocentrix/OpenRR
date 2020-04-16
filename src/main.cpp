#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "CaveMap.hpp"

int main(int, char **)
{
    std::cout << "Hello, world!\n";

    sf::RenderWindow w(sf::VideoMode(800, 600), "Hello, world!");
    sf::View view(sf::FloatRect(0, 0, 800, 600));

    CaveMap map(10, 5);

    sf::Clock clock;

    while (w.isOpen())
    {
        
        float dt = clock.restart().asSeconds();

        sf::Event e;
        while (w.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                w.close();
            }

            if (e.type == sf::Event::Resized)
            {
                view.setSize(e.size.width, e.size.height);
            }

            if (e.type == sf::Event::MouseButtonPressed)
            {
                if (e.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f pos = w.mapPixelToCoords(sf::Mouse::getPosition(w));
                    
                    map.drill(pos.x/50, pos.y/50);
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

        w.setView(view);
        w.clear(sf::Color::Black);
        map.draw(w);
        w.display();
    }

    std::cout << map.getTile(0, 0).getType() << std::endl;
    std::cout << map.getTile(1, 1).getType() << std::endl;
    std::cout << map.getTile(9, 1).getType() << std::endl;
    std::cout << map.getTile(1, 5).getType() << std::endl;
}
