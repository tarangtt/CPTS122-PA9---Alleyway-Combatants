#include "_libs.hpp"
#include <SFML/Graphics.hpp>

//only works in debug mode for some reason

int main()
{
    sf::RenderWindow window(sf::VideoMode({ SCREEN_WIDTH , SCREEN_HEIGHT }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    GameState current = MainMenu;
    //sf::Sprite backgroundSprite(imagepath);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else
                switch (current) {
                case MainMenu:
                    
                    break;
                case CharSelect:
                    //backgroundSprite.setTexture();

                    break;
                case InGame:
                    //backgroundSprite.setTexture();

                    break;
                case Paused:
                    //backgroundSprite.setTexture();

                    break;
                case Gameover:
                    //backgroundSprite.setTexture();

                    break;
                }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}