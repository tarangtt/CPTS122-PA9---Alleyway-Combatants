#include "_libs.hpp"
#include <SFML/Graphics.hpp>
#include "MainMenu.hpp"

//only works in debug mode for some reason

int main(void)
{
    sf::RenderWindow window(sf::VideoMode({ SCREEN_WIDTH , SCREEN_HEIGHT }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    GameState current = mainmenu;
    Texture mainBack("mainBackground.png");
    MainMenu main(mainBack);
    //sf::Sprite backgroundSprite(imagepath);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else {
                if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                    {
                        switch (current) {
                        case mainmenu:
                            main.checkStart(window, mouseButtonPressed);
                            main.checkExit(window, mouseButtonPressed);
                            break;
                        case charselect:
                            break;
                        case ingame:
                            break;
                        case gameover:
                            break;
                        }
                    }
                }
            }

        }

        window.clear();

        switch (current) {
        case mainmenu:
            main.renderMain(window, current);
            break;
        case charselect:
            
            break;
        case ingame:
            //backgroundSprite.setTexture();

            break;
        case paused:
            //backgroundSprite.setTexture();

            break;
        case gameover:
            //backgroundSprite.setTexture();

            break;
        }
        window.display();
    }
}
