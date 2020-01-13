#pragma once
#include "Component.h"
#include "Map.h"



class Mob : public Component{
protected:
	/*queue <pair<int, int>>* myQueue;
	int Visited[_X_MAP_BOUND][_Y_MAP_BOUND];
	int motionFlag;*/
	int health;
	Component* heroRefference;
	int mobDamage;
	int heroX, heroY; // used to find the current hero location on the tile map

public:

	int mobIndex;


	Mob(const char* filePath, int xPos, int yPos, int health, Component* hero, int mobDMG);

	~Mob() {
		//delete myQueue;
	}

	/*void inactiveUpdate() {
		yPos += motionFlag * 1;
		destinationRectangle.y = yPos * SCALESIZE;
		destinationRectangle.x = xPos * SCALESIZE;
		motionFlag = -motionFlag;
	}
	*/
	
	void decreaseHealth(int damage) override {
		health -= damage;
	}
	void update() override;
	void resetLee(const int newRow, const int newColumn) {}
	int getCurrentLife() override {
		return health;
	}

	void setHeroRefference(Component* givenHero) override{
		heroRefference = givenHero;
	}

	bool playerIsInVision(int givenDistance);


	static bool raceCondition(const int givenRow, const int givenColumn) {}
	static int mobCounter;
	static int movementTime;


};
