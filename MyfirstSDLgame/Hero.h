#pragma once
#include "Component.h"
#include "Map.h"

class Hero : public Component{
private:
// particular private attributes for the component
int direction;

public:

	Hero(const char* filePath, int xPos, int yPos, int health) : Component(filePath, xPos, yPos, health) {};

	void update();






};