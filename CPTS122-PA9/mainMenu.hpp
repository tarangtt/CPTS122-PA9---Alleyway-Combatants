// MAIN MENU

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "_libs.hpp"

using namespace std;
using namespace sf;

class MainMenu {
public:
	MainMenu(Texture& as);

	void renderMain(sf::RenderWindow& window, GameState& current);

	void checkStart(sf::RenderWindow& window, const sf::Event::MouseButtonPressed* MBP);

	void checkExit(sf::RenderWindow& window, const sf::Event::MouseButtonPressed* MBP);

private:
	int start = 0, x = 0, change = 0;
	sf::RectangleShape buttonStart;
	sf::RectangleShape buttonExit;
	sf::Sprite backgroundSprite;
};

