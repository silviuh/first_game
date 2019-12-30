#pragma once
#include "Component.h"
#include "Map.h"

class Hero : public Component{
private:
// particular private attributes for the component
int direction;
int oldCoordinateX, oldCoordinateY;


public:

	Hero(const char* filePath, int xPos, int yPos, int health) : Component(filePath, xPos, yPos, health) {
		oldCoordinateX = xPos;
		oldCoordinateY = yPos;
	};


	void resetLee(const int, const int) override {}
	void update();
};