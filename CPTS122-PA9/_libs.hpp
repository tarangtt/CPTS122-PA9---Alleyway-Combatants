#pragma once

#include <iostream>
#include <string>

typedef unsigned int uint;

using std::cin; // cin >> 
using std::cout; // cout <<
using std::endl;
using std::cerr; //error output

using std::string;
using std::to_string; //for the time stuff

#define SCREEN_HEIGHT 720 
#define SCREEN_WIDTH  1280


//SMFL libs
#include <SFML/Graphics.hpp>



#define RST "\033[0;0m"
#define RED "\033[0;31m"
#define GRN "\033[0;32m"
#define YEL "\033[0;33m"
#define BLU "\033[0;34m"
#define MAG "\033[0;35m"
#define CYN "\033[0;36m"