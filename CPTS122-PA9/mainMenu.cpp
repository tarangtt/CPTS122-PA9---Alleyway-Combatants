#include "mainMenu.hpp"

void renderMain(sf::RenderWindow& window)
{
	sf::Texture background;
	if (!background.loadFromFile("mianBackground.png")) {
		return; // Exit if the image fails to load
	}
	sf::Sprite backgroundSprite(background);

	// Create start button
	sf::RectangleShape buttonStart(sf::Vector2f(200.f, 50.f)); // Size: 200x50
	sf::Vector2f pos1(3, 6);

	// Create exit button
	sf::RectangleShape buttonExit(sf::Vector2f(200.f, 50.f)); // Size: 200x50
	sf::Vector2f pos2(20, 6);

	


	window.draw(backgroundSprite);


}
