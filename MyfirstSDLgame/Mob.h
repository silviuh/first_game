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

	bool playerIsInVision(int givenDistance);


	static bool raceCondition(const int givenRow, const int givenColumn) {}
	static int mobCounter;
	static int movementTime;


};


//
//void Mob::update() {
//	// we will use the lee algo
//	visitedMap[this->xPos][this->yPos] = VISITED;
//	myQueue->push(make_pair(this->xPos, this->yPos));
//
//	while (!myQueue.empty()) {
//		int i = myQueue.front().first;
//		int j = myQueue.front().second;
//		myQueue.pop();
//		for (int dir = 0; dir < 4; dir++) {
//			int newRow = i + dirX[dir];
//			int newColumn = j + dirY[dir];
//
//			// m am gandit sa am un visited pentru fiecare mob in partw
//			// la race condition m am gandit sa tin un vector cu toate pozitiile curente ale 
//			// mobilor si la fiecare if sa verific sa nu se suprapuna intre ei
//			if (
//				false == raceCondition(mobCoordinates, newRow, newColumn) and
//				true == insideBoundaries(newRow, newColumn) and
//				Game::level1Map[newColumn][newRow] > 0 and
//				VISITED != this->Visited[newColumn][newRow]
//				) {
//
//				this->Visited[newColumn][newRow] = VISITED;
//				myQueue.push(make_pair(newRow, newColumn));
//			}
//		}
//
//	}