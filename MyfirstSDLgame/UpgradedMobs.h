#pragma once
#include "Mob.h"
class UpgradedMobs : public Mob{
public:
	UpgradedMobs(const char* filePath, int xPos, int yPos, int health, Component* hero, int mobDMG);

	void setHeroRefference(Component* givenHero) override {
		heroRefference = givenHero;
	}

	virtual ~UpgradedMobs();
	void update() override;
};

