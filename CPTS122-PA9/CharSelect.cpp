#include "CharSelect.hpp"

CharSelect::CharSelect(Texture& background, Texture& select, Texture& Yuta, Texture& Tarang, Texture& John) :
	backgroundSprite(background), p1Select(select), p2Select(select), 
	p1BYuta(Yuta), p1BTarang(Tarang), p1BJohn(John), p1SYuta(Yuta), p1STarang(Tarang), p1SJohn(John),
	p2BYuta(Yuta), p2BTarang(Tarang), p2BJohn(John), p2SYuta(Yuta), p2STarang(Tarang), p2SJohn(John) {

	// Set p1Select button
	sf::Vector2f pos1(119, 501); // 119,   237 , 354
	p1Select.setPosition(pos1); 

	// Set p2Select button
	sf::Vector2f pos2(809, 501); // 809,  927 , 1044
	p2Select.setPosition(pos2);


}

void CharSelect::renderChar(sf::RenderWindow& window, GameState& current)
{
	if (!start) {
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
	window.draw(p1BYuta);
	window.draw(p1BTarang);
	window.draw(p1BJohn);
	window.draw(p1SYuta);
	window.draw(p1STarang);
	window.draw(p1SJohn);
	window.draw(p2BYuta);
	window.draw(p2BTarang);
	window.draw(p2BJohn);
	window.draw(p2SYuta);
	window.draw(p2STarang);
	window.draw(p2SJohn);
	window.draw(p1Select);
	window.draw(p2Select);
}

void CharSelect::p1Displace(int i)
{
	sf::Vector2f pos1(119, 501); // 119,   237 , 354
	sf::Vector2f pos2(237, 501); // 119,   237 , 354
	sf::Vector2f pos3(354, 501); // 119,   237 , 354

	switch (i) {
	case 1:
		if (p1 == 2) {
			p1Select.setPosition(pos1);
			p1--;
		}
		else if (p1 == 3) {
			p1Select.setPosition(pos2);
			p1--;
		}
		break;
	case 2:
		if (p1 == 1) {
			p1Select.setPosition(pos2);
			p1++;
		}
		else if (p1 == 2) {
			p1Select.setPosition(pos3);
			p1++;
		}
		break;
	case 3:
		break;
	}
}

void CharSelect::p2Displace(int i)
{
	switch (i) {
	case 1:

		break;
	case 2:
		break;
	case 3:
		break;
	}
}
