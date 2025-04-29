#include "CharSelect.hpp"

CharSelect::CharSelect(Texture& background, Texture& select, Texture& Yuta, Texture& Tarang, Texture& John, Texture& miniYuta, Texture& miniTarang, Texture& miniJohn) :
	backgroundSprite(background), p1Select(select), p2Select(select), 
	p1BYuta(Yuta), p1BTarang(Tarang), p1BJohn(John), p1SYuta(miniYuta), p1STarang(miniTarang), p1SJohn(miniJohn),
	p2BYuta(Yuta), p2BTarang(Tarang), p2BJohn(John), p2SYuta(miniYuta), p2STarang(miniTarang), p2SJohn(miniJohn) {

	
	// Set p1Select button
	sf::Vector2f pos1(119, 501); // 119,   237 , 354
	p1Select.setPosition(pos1); 

	// Set p2Select button
	sf::Vector2f pos2(809, 501); // 809,  927 , 1044
	p2Select.setPosition(pos2);

	sf::Vector2f posB1(142, 90);
	p1BYuta.setPosition(posB1);
	p1BTarang.setPosition(posB1);
	p1BJohn.setPosition(posB1);

	sf::Vector2f posB2(832, 90);
	p2BYuta.setPosition(posB2);
	p2BTarang.setPosition(posB2);
	p2BJohn.setPosition(posB2);

	sf::Vector2f pos1s1(120, 500); // 120,   236 , 352
	p1SYuta.setPosition(pos1s1);
	sf::Vector2f pos2s1(236, 500); // 120,   236 , 352
	p1STarang.setPosition(pos2s1);
	sf::Vector2f pos3s1(352, 500); // 120,   236 , 352
	p1SJohn.setPosition(pos3s1);


	sf::Vector2f pos1s2(810, 500); // 810,  926 , 1042
	p2SYuta.setPosition(pos1s2);
	sf::Vector2f pos2s2(926, 500); // 810,  926 , 1042
	p2STarang.setPosition(pos2s2);
	sf::Vector2f pos3s2(1042, 500); // 810,  926 , 1042
	p2SJohn.setPosition(pos3s2);
}

void CharSelect::renderChar(sf::RenderWindow& window, GameState& current)
{
	if (!start) {
		setColors(x);
		Sleep(1);
		x += 2;
		if (x > 253) {
			x = 255;
			start = 1;
			resetColor();
		}
	}
	if (change) {
		setColors(x);
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
	switch (p1) {
	case 1:
	window.draw(p1BYuta);
		break;
	case 2:
	window.draw(p1BTarang);
		break;
	case 3:
	window.draw(p1BJohn);
		break;
	}
	switch (p2) {
	case 1:
		window.draw(p2BYuta);
		break;
	case 2:
		window.draw(p2BTarang);
		break;
	case 3:
		window.draw(p2BJohn);
		break;
	}
	setHue(p1, p2);
	window.draw(p1SYuta);
	window.draw(p1STarang);
	window.draw(p1SJohn);
	window.draw(p2SYuta);
	window.draw(p2STarang);
	window.draw(p2SJohn);
	window.draw(p1Select);
	window.draw(p2Select);
}

void CharSelect::p1Displace(int i)
{
	sf::Vector2f pos1(121, 501); // 120,   236 , 352
	sf::Vector2f pos2(237, 501); // 120,   236 , 352
	sf::Vector2f pos3(353, 501); // 120,   236 , 352

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
	sf::Vector2f pos1(811, 501); // 810,  926 , 1042
	sf::Vector2f pos2(927, 501); // 810,  926 , 1042
	sf::Vector2f pos3(1043, 501); // 810,  926 , 1042

	switch (i) {
	case 1:
		if (p2 == 2) {
			p2Select.setPosition(pos1);
			p2--;
		}
		else if (p2 == 3) {
			p2Select.setPosition(pos2);
			p2--;
		}
		break;
	case 2:
		if (p2 == 1) {
			p2Select.setPosition(pos2);
			p2++;
		}
		else if (p2 == 2) {
			p2Select.setPosition(pos3);
			p2++;
		}
		break;
	case 3:
		break;
	}
}

sf::Sprite& CharSelect::p1CurrentSprite(int i)
{
	if (i == 1) {
		return p1BYuta;
	}
	else if (i == 2) {
		return p1BTarang;
	}
	else {
		return p1BJohn;
	}
}

sf::Sprite& CharSelect::p2CurrentSprite(int i)
{
	if (i == 1) {
		return p2BYuta;
	}
	else if (i == 2) {
		return p2BTarang;
	}
	else {
		return p2BJohn;
	}
}

void CharSelect::resetColor(void) {
	p1BYuta.setColor(sf::Color(x, x, x));
	p1BTarang.setColor(sf::Color(x, x, x));
	p1BJohn.setColor(sf::Color(x, x, x));
	p2BYuta.setColor(sf::Color(x, x, x));
	p2BTarang.setColor(sf::Color(x, x, x));
	p2BJohn.setColor(sf::Color(x, x, x));
}

void CharSelect::setColors(int x)
{
	backgroundSprite.setColor(sf::Color(x, x, x));
	p1CurrentSprite(p1).setColor(sf::Color(x, x, x));
	p2CurrentSprite(p2).setColor(sf::Color(x, x, x));
	p1SYuta.setColor(sf::Color(x, x, x));
	p1STarang.setColor(sf::Color(x, x, x));
	p1SJohn.setColor(sf::Color(x, x, x));
	p2SYuta.setColor(sf::Color(x, x, x));
	p2STarang.setColor(sf::Color(x, x, x));
	p2SJohn.setColor(sf::Color(x, x, x));
}

void CharSelect::setHue(int p1, int p2)
{
	switch (p1) {
	case 1:
		p1STarang.setColor(sf::Color(255, 255, 255, 128));
		p1SJohn.setColor(sf::Color(255, 255, 255, 128));
		p1SYuta.setColor(sf::Color(255, 255, 255, 255));
		break;
	case 2:
		p1SYuta.setColor(sf::Color(255, 255, 255, 128));
		p1SJohn.setColor(sf::Color(255, 255, 255, 128));
		p1STarang.setColor(sf::Color(255, 255, 255, 255));
		break;
	case 3:
		p1SYuta.setColor(sf::Color(255, 255, 255, 128));
		p1STarang.setColor(sf::Color(255, 255, 255, 128));
		p1SJohn.setColor(sf::Color(255, 255, 255, 255));
		break;
	}
	switch (p2) {
	case 1:
		p2STarang.setColor(sf::Color(255, 255, 255, 128));
		p2SJohn.setColor(sf::Color(255, 255, 255, 128));
		p2SYuta.setColor(sf::Color(255, 255, 255, 255));
		break;
	case 2:
		p2SYuta.setColor(sf::Color(255, 255, 255, 128));
		p2SJohn.setColor(sf::Color(255, 255, 255, 128));
		p2STarang.setColor(sf::Color(255, 255, 255, 255));
		break;
	case 3:
		p2SYuta.setColor(sf::Color(255, 255, 255, 128));
		p2STarang.setColor(sf::Color(255, 255, 255, 128));
		p2SJohn.setColor(sf::Color(255, 255, 255, 255));
		break;
	}
}

