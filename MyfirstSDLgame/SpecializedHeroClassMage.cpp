#include "SpecializedHeroClassMage.h"


void SpecializedHeroClassMage::castAbility() {
	float minimumProximity = MAX_VALUE;
	int targetIndex;

	if (abilityActivated == true and abilityCanBeCasted == true) {
		setAbilityColdown();
		abilityCanBeCasted = false;
		for (int i = 0; i < mobArray.size(); i++) {
			if (mobArray.at(i)->isComponentActive() == true) {
				int xd = abs(mobArray.at(i)->getXpos() - this->xPos);
				int yd = abs(mobArray.at(i)->getYpos() - this->yPos);

				float proximity = sqrt(xd * xd + yd * yd);
				if (minimumProximity > proximity) {
					minimumProximity = proximity;
					targetIndex = i;
				}
			}
		}
		mobArray.at(targetIndex)->makeComponentInactive();
	}
}


void SpecializedHeroClassMage::update() {
	Hero::update();
	castAbility();
	abilityActivated = false;
}