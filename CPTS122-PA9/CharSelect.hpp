// CHARACTER SELECTION

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "_libs.hpp"

using namespace std;
using namespace sf;

class CharSelect {
public:
	CharSelect(Texture& as);

	void renderChar(sf::RenderWindow& window, GameState& current);

private:
	int start = 0, x = 0, change = 0;
	sf::Sprite backgroundSprite;
};

