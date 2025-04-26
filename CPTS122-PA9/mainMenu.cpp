#include "mainMenu.hpp"



mainMenu::mainMenu(Texture& as) : backgroundSprite(as), buttonStart(sf::Vector2f(400.f, 100.f)), buttonExit(sf::Vector2f(400.f, 100.f))
{

	// Create start button
	sf::Vector2f pos1(150, 500);
	buttonStart.setPosition(pos1);
	buttonStart.setFillColor(sf::Color::Transparent);

	// Create exit button
	sf::Vector2f pos2(730, 500);
	buttonExit.setPosition(pos2);
	buttonExit.setFillColor(sf::Color::Transparent);
	
}

void mainMenu::renderMain(sf::RenderWindow& window)
{

	window.draw(backgroundSprite);
	window.draw(buttonStart);
	window.draw(buttonExit);
}

void mainMenu::checkStart(sf::RenderWindow& window, const sf::Event::MouseButtonPressed* MBP, GameState& current)
{
	sf::Vector2i pixelPos(MBP->position.x, MBP->position.y);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	if (buttonStart.getGlobalBounds().contains(static_cast<sf::Vector2f>(worldPos))) {
		current = CharSelect;
	}
}

void mainMenu::checkExit(sf::RenderWindow& window, const sf::Event::MouseButtonPressed* MBP)
{
	sf::Vector2i pixelPos(MBP->position.x, MBP->position.y);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	if (buttonExit.getGlobalBounds().contains(static_cast<sf::Vector2f>(worldPos))) {
		window.close();
	}
}
