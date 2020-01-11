#include "SpecializedHeroKnight.h"

void SpecializedHeroKnight::castAbility() {
	if (abilityActivated == true and abilityCanBeCasted == true) {
		setAbilityColdown();
		abilityCanBeCasted = false;
		for (int i = 0; i < mobArray.size(); i++) {
			if (mobArray.at(i)->isComponentActive() == true and inRangeForEarthSmash(mobArray.at(i)->getXpos(), mobArray.at(i)->getYpos()) ) {
				mobArray.at(i)->decreaseHealth(EARTH_SMASH_DAMAGE);
			}
		}
		
	}
}

void SpecializedHeroKnight::update() {
	Hero::update();
	castAbility();
	abilityActivated = false;
}


SpecializedHeroKnight::~SpecializedHeroKnight()
{
}
