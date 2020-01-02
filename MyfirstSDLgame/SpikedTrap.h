#pragma once
#include "Trap.h"
class SpikedTrap : public Trap{
private:
	int scoreBonus;
public:
	SpikedTrap(const char* imgToLoad, int xPos, int yPos);
	virtual ~SpikedTrap();
	void update() override {}
	void resetLee(const int, const int) override {}
};

