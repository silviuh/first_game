#pragma once
#include "Component.h"
#include "Map.h"



class Mob : public Component{
private:
	int motionFlag;

public:

	Mob(const char* filePath, int xPos, int yPos, int health) : Component(filePath, xPos, yPos, health) {
		motionFlag = -1;
	}


	void update() override;


};