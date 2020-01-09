#pragma once
#include "Component.h"
class HeartBonus : public Component {
private:
	int givenBonus;
	Component* heroReference;
public:
	HeartBonus(const char* imgToLoad, int xPos, int yPos, int health, int bonus, Component* heroRef) : Component(imgToLoad, xPos, yPos, health) {
		givenBonus = bonus;
		destinationRectangle.x = xPos * SCALESIZE;
		destinationRectangle.y = yPos * SCALESIZE;
		heroReference = heroRef;
	}
	virtual ~HeartBonus();
	void HeroGetsBonus() {
		isActive = false;
		if(heroReference->getCurrentLife() + givenBonus > MAX_HERO_HEALTH)
			heroReference->increaseHealth(MAX_HERO_HEALTH - heroReference->getCurrentLife());
		else
			heroReference->increaseHealth(givenBonus);
	}

	void setHeroRefference(Component* givenHero) override {
		heroReference = givenHero;
	}

	void update() override {

	}
	void resetLee(const int, const int) override {}
};

