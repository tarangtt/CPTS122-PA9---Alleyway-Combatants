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
    Texture Yuta("TestYuta.png"); //298px
    Texture Tarang("TestTarang.jpg");
    Texture John("TestJohn.jpg");
    Texture miniYuta("TestMiniYuta.png"); //114px
    Texture miniTarang("TestMiniTarang.jpg");
    Texture miniJohn("TestMiniJohn.jpg");
    CharSelect charSelect(charBack, selectText, Yuta, Tarang, John, miniYuta, miniTarang, miniJohn);

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
                        charSelect.p1Displace(1);
                    }
                    else if (keyPressed->scancode == sf::Keyboard::Scan::D) {
                        charSelect.p1Displace(2);
                    }
                    else if (keyPressed->scancode == sf::Keyboard::Scan::S) {
                        charSelect.p1Displace(3);
                    }
                    else if (keyPressed->scancode == sf::Keyboard::Scan::J) {
                        charSelect.p2Displace(1);
                    }
                    else if (keyPressed->scancode == sf::Keyboard::Scan::L) {
                        charSelect.p2Displace(2);
                    }
                    else if (keyPressed->scancode == sf::Keyboard::Scan::K) {
                        charSelect.p2Displace(3);
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
