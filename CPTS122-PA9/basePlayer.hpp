#pragma once

#include "_libs.hpp"


typedef struct spritePack
{
	std::string path;
	sf::Texture texture;
	sf::Sprite sprite;

} sprites;

class BasePlayer
{
protected:
	//health
	uint healthCurr;
	uint healthMax;

	//defense
	float damageReduction; //defense reduction (%/100) (less than 1 = lower dmg; greater than 1 = higher dmg) 
	//movement speed
	uint movementSpeed;

	//attack
	uint attackDamageBase;
	uint attackMaxCharge;
	
	//jump
	uint jumpHeightBase; 
	uint jumpHeightMaxCharge; 
	uint weight; //gravity 
	
	//===Sprites===
	sprites  characterWalk1, characterWalk2, characterBlock, characterJump;
	sprites  characterHighAttackLaunch, characterHighAttackCharge; //punch
	sprites  characterLowAttackLaunch, characterLowAttackCharge; // kick
	


public:
	void draw()
	{

	}


};