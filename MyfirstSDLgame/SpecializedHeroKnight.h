#pragma once
#include "Hero.h"
class SpecializedHeroKnight : public Hero{
private:
	Map* levelMap;
	vector <Component*> mobArray;

public:
	SpecializedHeroKnight(const char* filePath, int xPos, int yPos, int health, Map* levelMap) : Hero(filePath, xPos, yPos, health) {
		this->levelMap = levelMap;
		abilityColdown = EARTH_SMASH_COLDOWN;
		abilityCanBeCasted = true;
	}

	void update() override;
	void castAbility();
	void reduceAbilityColdown() {
		abilityColdown--;
	}
	void setAbilityColdown() {
		abilityColdown = INSTANT_KILL_COLDOWN;
	}

	void toogleAbilityCanBeCastedFlag() {
		abilityCanBeCasted = !abilityCanBeCasted;
	}

	virtual int getAbilityColdown() {
		return abilityColdown;
	}

	void addMobsArr(vector <Component*> mobArray) {
		this->mobArray = mobArray;
	}

	bool inRangeForEarthSmash(int givenX, int givenY) {
		return xPos == givenX or yPos == givenY;
	}


	~SpecializedHeroKnight();
};

