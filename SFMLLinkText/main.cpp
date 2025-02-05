#include <SFML/Graphics.hpp>
#include "ParticleSystem.cpp"
#include <iostream>
#include <SFML/Audio.hpp>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({ 512, 256 }), "Particles");
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("res/music/splat.ogg")) {
        std::cout << "Falha no carregamendo do efeito" << std::endl;
        system("pause");
    }
    sf::Texture texture("res/img/brind.jpg", false, sf::IntRect({ 10, 10 }, { 32, 32 }));
    sf::Font fontArial;
    sf::Vector2i positionMouse = sf::Mouse::getPosition(window);
    if (!fontArial.openFromFile("res/font/LEMONMILKRegular.otf"))
    {
        std::cout << "Falha no carregamendo da font" << std::endl;
        system("pause");
    }
    sf::Text positionX(fontArial);
    sf::Text positionY(fontArial);
    sf::Sound sound(buffer);
    


    positionX.setPosition({ 10.f, 50.f });
    positionY.setPosition({ 10.f, 80.f });    
    positionX.setCharacterSize(24);
    positionY.setCharacterSize(24);
    positionX.setFillColor(sf::Color::White);
    positionY.setFillColor(sf::Color::White);
    positionX.setStyle(sf::Text::Bold | sf::Text::Underlined);
    positionY.setStyle(sf::Text::Bold | sf::Text::Underlined);


    if (!texture.loadFromFile("res/img/brind.jpg"))
    {
        std::cout << "Falha no carregamendo da textura" << std::endl;
        system("pause");
    }
    sf::Sprite sprite(texture);

    // create the particle system
    ParticleSystem particles(1000);

    // create a clock to track the elapsed time
    sf::Clock clock;

    // run the main loop
    while (window.isOpen())
    {
        // handle events
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // make the particle system emitter follow the mouse
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        particles.setEmitter(window.mapPixelToCoords(mouse));

        // update it
        sf::Time elapsed = clock.restart();
        particles.update(elapsed);

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        std::cout << "Posição do Mouse - X: " << mousePos.x << ", Y: " << mousePos.y << std::endl;

        positionX.setString("Posição X: " + std::to_string(positionMouse.x));
        positionY.setString("Posição Y: " + std::to_string(positionMouse.y));

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sound.play();
        }

        // draw it
        window.clear();
        window.draw(sprite);
        window.draw(particles);
        window.draw(positionX);
        window.draw(positionY);
        window.display();
    }
}