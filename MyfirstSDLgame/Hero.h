#pragma once
#include "Component.h"
#include "Map.h"

class Hero : public Component{
private:
// particular private attributes for the component
int direction;
int oldCoordinateX, oldCoordinateY;
int score;


public:

	Hero(const char* filePath, int xPos, int yPos, int health) : Component(filePath, xPos, yPos, health) {
		oldCoordinateX = xPos;
		oldCoordinateY = yPos;
		score = 0;
	};

	int getCurrentScore() override{
		return score;
	}

	int getCurrentLife() override {
		return health;
	}

	void resetLee(const int, const int) override {}
	void update();
	void increaseScore(int number);
	void decreaseHealth(int damage);
	void increaseHealth(int givenHealth) {
		health += givenHealth;
	}
};