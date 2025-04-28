#pragma once

#include <iostream>
#include <string>
#include <Windows.h>

#include <chrono> //tarang didnt know smfl had a sf:;Clock :/

//SMFL libs
#include <SFML/Graphics.hpp>

//typedefs / structs
typedef unsigned int uint;

class spritePack
{
public:
    string path;
    sf::Texture texture;
    sf::Sprite sprite;

    spritePack(string filename)
        : path(filename), texture(sf::Texture(path)), sprite(sf::Sprite(texture))
    {}

    spritePack()
        : path(""), texture("missingTexture.png"), sprite(sf::Sprite(texture))
    {}
};


//constants
#define SCREEN_HEIGHT 720 
#define SCREEN_WIDTH  1280

// these dont work as #defines in SMFL idk why
const float PLAYER_HEIGHT = 450.0f * 0.6f;
const float MAX_JUMP_HEIGHT = (2 * PLAYER_HEIGHT) - 25.f;
const float groundY = SCREEN_HEIGHT - 70.f;

enum GameState {mainmenu, charselect, ingame, paused, gameover};

enum class JumpType {
    None,
    Straight,
    Forward,
    Backward
};

enum class AttackType {
    None,
    High,
    Low
};

enum class ChargeType {
    None,
    Attack,
    Jump
};


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