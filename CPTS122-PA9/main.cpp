#include "_libs.hpp"
#include <SFML/Graphics.hpp>
#include "MainMenu.hpp"
#include "CharSelect.hpp"

//only works in debug mode for some reason

int main(void)
{
    sf::RenderWindow window(sf::VideoMode({ SCREEN_WIDTH , SCREEN_HEIGHT }), "SFML works!");

    GameState current = mainmenu;
    Texture mainBack("mainBackground.png");
    MainMenu mainMenu(mainBack);

    Texture charBack("charBackground.png");
    Texture selectText("selected.png");
    Texture Yuta("selected.png");
    Texture Tarang("selected.png");
    Texture John("selected.png");
    CharSelect charSelect(charBack, selectText, Yuta, Tarang, John);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    switch (current) {
                    case mainmenu:
                        mainMenu.checkStart(window, mouseButtonPressed);
                        mainMenu.checkExit(window, mouseButtonPressed);
                        break;
                    case ingame:
                        break;
                    case gameover:
                        break;
                    }
                }
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (current == charselect) {
                    if (keyPressed->scancode == sf::Keyboard::Scan::A) {

                    }
                    else if (keyPressed->scancode == sf::Keyboard::Scan::D) {

                    }
                    else if (keyPressed->scancode == sf::Keyboard::Scan::S) {

                    }
                    else if (keyPressed->scancode == sf::Keyboard::Scan::J) {

                    }
                    else if (keyPressed->scancode == sf::Keyboard::Scan::K) {

                    }
                    else if (keyPressed->scancode == sf::Keyboard::Scan::I) {

                    }
                }
                else if (current == ingame) {

                }
                else {

                }

            }

        }

        window.clear();

        switch (current) {
        case mainmenu:
            mainMenu.renderMain(window, current);
            break;
        case charselect:
            charSelect.renderChar(window, current);
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
