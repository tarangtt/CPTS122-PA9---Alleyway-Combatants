#include "mainMenu.hpp"

void renderMain(sf::RenderWindow& window)
{
	sf::Texture background;
	if (!background.loadFromFile("mianBackground.png")) {
		return; // Exit if the image fails to load
	}
	sf::Sprite backgroundSprite(background);

	// Create a button (RectangleShape)
	sf::RectangleShape button(sf::Vector2f(200.f, 50.f)); // Size: 200x50
	sf::Vector2f pos(3,6);

	// 
	
	button.setPosition(pos);
	window.draw(backgroundSprite);


}
