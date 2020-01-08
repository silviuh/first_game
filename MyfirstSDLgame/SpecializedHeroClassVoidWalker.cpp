#include "SpecializedHeroClassVoidWalker.h"


SpecializedHeroClassVoidWalker::~SpecializedHeroClassVoidWalker(){
}

void SpecializedHeroClassVoidWalker::castAbility() {
	if (abilityActivated == true and abilityCanBeCasted == true) {
		setAbilityColdown();
		abilityCanBeCasted = false;

		int xPos,  yPos;
		do {
			xPos = rand() % (_X_MAP_BOUND - 3) + 2;
			yPos = rand() % (_Y_MAP_BOUND - 3) + 2;
		} while (levelMap->accesMapCoordinates(xPos, yPos) < 0);

		this->xPos = xPos;
		this->yPos = yPos;
	}
}


void SpecializedHeroClassVoidWalker::update() {
	Hero::update();
	castAbility();
	abilityActivated = false;
}