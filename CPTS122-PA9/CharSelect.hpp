// CHARACTER SELECTION

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "_libs.hpp"

using namespace std;
using namespace sf;

class CharSelect {
public:
	CharSelect(Texture& background, Texture& select, Texture& Yuta, Texture& Tarang, Texture& John, Texture& miniYuta, Texture& miniTarang, Texture& miniJohn);

	void renderChar(sf::RenderWindow& window, GameState& current);

	void p1Displace(int i);

	void p2Displace(int i);

	int getP1Selection() const { return p1; }
	int getP2Selection() const { return p2; }


private:
	int start = 0, x = 0, change = 0;
	sf::Sprite backgroundSprite;
	sf::Sprite p1Select;
	sf::Sprite p2Select;
	int p1 = 1, p2 = 1, p1Decided = 0, p2Decided = 0;
	sf::Sprite p1BYuta;
	sf::Sprite p1BTarang;
	sf::Sprite p1BJohn;
	sf::Sprite p1SYuta;
	sf::Sprite p1STarang;
	sf::Sprite p1SJohn;
	sf::Sprite p2BYuta;
	sf::Sprite p2BTarang;
	sf::Sprite p2BJohn;
	sf::Sprite p2SYuta;
	sf::Sprite p2STarang;
	sf::Sprite p2SJohn;

	sf::Sprite& p1CurrentSprite(int i);
	sf::Sprite& p2CurrentSprite(int i);

	void resetColor(void);
	void setColors(int x);
	void setHue(int p1, int p2);
};