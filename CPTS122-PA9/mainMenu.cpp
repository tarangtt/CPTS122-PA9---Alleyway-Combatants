#include "MainMenu.hpp"

MainMenu::MainMenu(Texture& as) : backgroundSprite(as), buttonStart(sf::Vector2f(400.f, 100.f)), buttonExit(sf::Vector2f(400.f, 100.f))
{

	//Create start button
	sf::Vector2f pos1(150, 500);
	buttonStart.setPosition(pos1);
	buttonStart.setFillColor(sf::Color::Transparent);

	//Create exit button
	sf::Vector2f pos2(730, 500);
	buttonExit.setPosition(pos2);
	buttonExit.setFillColor(sf::Color::Transparent);
	
}

void MainMenu::renderMain(sf::RenderWindow& window, GameState& current)
{
	if (!start && !change) {
		backgroundSprite.setColor(sf::Color(x, x, x));
		Sleep(1);
		x += 2;
		if (x > 253) {
			x = 255;
			start = 1;
		}
	}
	if (change) {
		backgroundSprite.setColor(sf::Color(x, x, x));
		Sleep(1);
		x -= 2;
		if (x < 0) {
			if (change == 1) {
				current = charselect;
			}
			else {
				window.close();
			}
			x = 255;
			change = 0;
		}
	}
	window.draw(backgroundSprite);
	window.draw(buttonStart);
	window.draw(buttonExit);
}

void MainMenu::checkStart(sf::RenderWindow& window, const sf::Event::MouseButtonPressed* MBP)
{
	sf::Vector2i pixelPos(MBP->position.x, MBP->position.y);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	if (buttonStart.getGlobalBounds().contains(static_cast<sf::Vector2f>(worldPos))) {
		change = 1;
	}
}

void MainMenu::checkExit(sf::RenderWindow& window, const sf::Event::MouseButtonPressed* MBP)
{
	sf::Vector2i pixelPos(MBP->position.x, MBP->position.y);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	if (buttonExit.getGlobalBounds().contains(static_cast<sf::Vector2f>(worldPos))) {
		change = 2;
	}
}