#pragma once
#include "Component.h"
#include "Map.h"

class Hero : public Component{
protected:
// particular private attributes for the component
	int direction;
	int oldCoordinateX, oldCoordinateY;
	int score;
	bool abilityActivated;

public:
	int abilityColdown;
	bool abilityCanBeCasted;

	Hero(const char* filePath, int xPos, int yPos, int health) : Component(filePath, xPos, yPos, health) {
		oldCoordinateX = xPos;
		oldCoordinateY = yPos;
		score = 0;
		abilityActivated = false;
		abilityColdown = 5;
	};

	void toogleOnAbility() {
		abilityActivated = true;
	}

	void toogleOffAbility() {
		abilityActivated = false;
	}

	int getCurrentScore() override{
		return score;
	}

	int getCurrentLife() override {
		return health;
	}

	void reduceAbilityColdown() {}
	void setAbilityColdown() {}
	void toogleAbilityCanBeCastedFlag() {}
	virtual int getAbilityColdown() {
		return abilityColdown;
	}


	void resetLee(const int, const int) override {}
	void update();
	void increaseScore(int number);
	void decreaseHealth(int damage);
	void increaseHealth(int givenHealth) {
		health += givenHealth;
	}
};