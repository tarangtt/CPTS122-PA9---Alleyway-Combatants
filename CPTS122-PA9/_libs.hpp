#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <chrono> //tarang didnt know smfl had a clock
#include <unordered_map> //python dictionary - using for textures

#include <SFML/Graphics.hpp>


typedef unsigned int uint;

//constants
#define SCREEN_HEIGHT 720 
#define SCREEN_WIDTH  1280

const float baseGravity = 0.03f;
const float baseJumpVelocity = -3.2f;
const float baseHorizontalJumpSpeed = 1.1f;
const float moveSpeed = 0.8f;
const float minChargeTime = 0.1f;
const float maxChargeTime = 3.0f;
const float maxChargeMultiplier = 2.5f;
const int baseAttackDamage = 10;
const float attackRange = 100.f;
const float highAttackHeightRatio = 2.2f;
const float lowAttackHeight = 100.f;
const float blockHeightReduction = 0.3f;
const float animationSwitchTime = 0.2f;

const float PLAYER_HEIGHT = 450.0f * 1.f;
const float MAX_JUMP_HEIGHT = (1.75 * PLAYER_HEIGHT) - 25.f;
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
    High,  //punch 
    Low    //kick 
};

enum class ChargeType {
    None,
    Attack,
    Jump
};

enum class CharacterState {
    Idle,
    Walking,
    Blocking,
    Jumping,
    HighAttackCharge,
    HighAttackLaunch,
    LowAttackCharge,
    LowAttackLaunch
};

enum class FightState {
    NotStarted = -1,
    Aborted,
    Ongoing,    
    P1Wins,     
    P2Wins,         
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