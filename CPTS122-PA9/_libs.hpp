#pragma once

#include <iostream>
#include <string>
#include <Windows.h>

//SMFL libs
#include <SFML/Graphics.hpp>

//typedefs / structs
typedef unsigned int uint;

typedef struct spritePack
{
	std::string path;
	sf::Texture texture;
	sf::Sprite sprite;

} sprites;

//constants
#define SCREEN_HEIGHT 720 
#define SCREEN_WIDTH  1280
#define GROUND_LEVEL 650.0

enum GameState {mainmenu, charselect, ingame, paused, gameover};


//using -- 
using std::cin; // cin >> 
using std::cout; // cout <<
using std::endl;
using std::cerr; //error output

using std::vector;

using std::string;
using std::to_string; //for the time stuff



//text colors 
#define RST "\033[0;0m"
#define RED "\033[0;31m"
#define GRN "\033[0;32m"
#define YEL "\033[0;33m"
#define BLU "\033[0;34m"
#define MAG "\033[0;35m"
#define CYN "\033[0;36m"