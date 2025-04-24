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
	float damageReduction; //defense reduction (%/100)

	//attack
	uint attackDamageBase; 
	uint chargedAttackMaxCharge;
	uint chargedAttackCurrCharge;
	
	//movement speed
	uint movementSpeedMax;

	//jump
	uint jumpHeightBase; 
	uint jumpHeightMaxCharge; //how high you go
	uint jumpHeightCurrCharge; //how high you go
	uint weight; //how fast you go back down
	
	//===Sprites===
	sprites  characterRest, characterBlock, characterJump, characterFloat;
	sprites  characterHighAttackLaunch, characterHighAttackCharge;
	sprites  characterLowAttackLaunch, characterLowAttackCharge;



};