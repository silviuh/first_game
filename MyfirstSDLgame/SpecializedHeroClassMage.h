#pragma once
#include "Mob.h"
#include "Hero.h"
class SpecializedHeroClassMage : public Hero {
private:
	Map* levelMap;
	vector <Component*> mobArray;

public:
	SpecializedHeroClassMage(const char* filePath, int xPos, int yPos, int health, Map* levelMap) : Hero(filePath, xPos, yPos, health) {
		this->levelMap = levelMap;
		abilityColdown = INSTANT_KILL_COLDOWN;
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

	~SpecializedHeroClassMage() {}
};

