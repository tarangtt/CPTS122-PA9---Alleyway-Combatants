// MAIN MENU

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "_libs.hpp"

using namespace std;
using namespace sf;

class mainMenu {
public:
	mainMenu(Texture& as);

	void renderMain(sf::RenderWindow& window);

	void checkStart(sf::RenderWindow& window, const sf::Event::MouseButtonPressed* MBP, GameState& current);

	void checkExit(sf::RenderWindow& window, const sf::Event::MouseButtonPressed* MBP);

private:
	sf::RectangleShape buttonStart;
	sf::RectangleShape buttonExit;
	sf::Sprite backgroundSprite;
};

