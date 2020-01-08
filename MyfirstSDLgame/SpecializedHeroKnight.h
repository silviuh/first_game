#pragma once
#include "Hero.h"
class SpecializedHeroKnight : public Hero{
private:
	Map* levelMap;

public:
	SpecializedHeroKnight(const char* filePath, int xPos, int yPos, int health, Map* levelMap) : Hero(filePath, xPos, yPos, health) {
		this->levelMap = levelMap;
		abilityColdown = VOID_HOLE_COLDOWN;
		abilityCanBeCasted = true;
	}
	~SpecializedHeroKnight();
};

