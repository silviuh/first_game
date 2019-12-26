#pragma once
#include "Component.h"
#include "Map.h"



class Mob : public Component{
private:
	int motionFlag;
	int heroX, heroY; // used to find the current hero location on the tile map
public:

	Mob(const char* filePath, int xPos, int yPos, int health) : Component(filePath, xPos, yPos, health) {
		motionFlag = -1;
	}


	void inactiveUpdate() {
		yPos += motionFlag * 1;
		destinationRectangle.y = yPos * SCALESIZE;
		destinationRectangle.x = xPos * SCALESIZE;
		motionFlag = -motionFlag;
	}
	void update() override;
	

};