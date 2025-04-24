#include "_libs.hpp"
#include <SFML/Graphics.hpp>

//only works in debug mode for some reason

int main(void)
{
    sf::RenderWindow window(sf::VideoMode({ SCREEN_WIDTH , SCREEN_HEIGHT }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}