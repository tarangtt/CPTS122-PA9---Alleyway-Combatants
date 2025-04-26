#include "mainMenu.hpp"

void renderMain(sf::RenderWindow& window)
{
	sf::Texture background;
	if (!background.loadFromFile("mainBackground.png")) {
		return; // Exit if the image fails to load
	}
	sf::Sprite backgroundSprite(background);

	// Create start button
	sf::RectangleShape buttonStart(sf::Vector2f(400.f, 100.f)); 
	sf::Vector2f pos1(150, 500);
	buttonStart.setPosition(pos1);
	buttonStart.setFillColor(sf::Color::Transparent);

	// Create exit button
	sf::RectangleShape buttonExit(sf::Vector2f(400.f, 100.f));
	sf::Vector2f pos2(730, 500);
	buttonExit.setPosition(pos2);
	buttonExit.setFillColor(sf::Color::Transparent);
	


	window.draw(backgroundSprite);
	window.draw(buttonStart);
	window.draw(buttonExit);
}
