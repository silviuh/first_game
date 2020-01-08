#pragma once
#include "Hero.h"
#include "TextureManager.h"

class SpecializedHeroClassVoidWalker : public Hero{
private:
	Map* levelMap;
public:

	SpecializedHeroClassVoidWalker(const char* filePath, int xPos, int yPos, int health, Map* levelMap) : Hero(filePath, xPos, yPos, health){
		this->levelMap = levelMap;
		abilityColdown = VOID_HOLE_COLDOWN;
		abilityCanBeCasted = true;
	}

	void update() override;
	void castAbility();
	void reduceAbilityColdown() {
		abilityColdown--;
	}
	void setAbilityColdown() {
		abilityColdown = VOID_HOLE_COLDOWN;
	}

	void toogleAbilityCanBeCastedFlag() {
		abilityCanBeCasted = !abilityCanBeCasted;
	}

	virtual int getAbilityColdown() {
		return abilityColdown;
	}

	virtual ~SpecializedHeroClassVoidWalker();
};

