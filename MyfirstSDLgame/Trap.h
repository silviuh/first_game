#pragma once
#include "Component.h"
class Trap : public Component{
private:
	bool isActive;
	int damage;


public:
	Trap(const char* imgToLoad, int xPos, int yPos, int health) : Component(imgToLoad, xPos, yPos, 0) {}
	virtual ~Trap();
	void update() override {}
	void resetLee(const int, const int) override {}
};

