#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 500, 500 }), "SFML works!");
    sf::RectangleShape rectangle(sf::Vector2f(100.f, 50.f));
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition({ 400.f, 300.f });

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        rectangle.rotate(sf::degrees(1.f));
        window.clear();
        window.draw(rectangle);
        window.display();
    }

}