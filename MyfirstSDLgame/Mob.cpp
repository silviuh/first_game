#include "Mob.h"

//void Mob::inactiveUpdate()  {
//	// move to north direction
//	yPos += motionFlag * 1;
//	destinationRectangle.y = yPos * SCALESIZE;
//	destinationRectangle.x = xPos * SCALESIZE;
//	motionFlag = -motionFlag;
//}

Mob::Mob(const char* filePath, int xPos, int yPos, int health, Component* hero, int mobDMG) : Component(filePath, xPos, yPos, health) {
	//motionFlag = -1;
	//myQueue = new queue <pair<int, int>>(); // queue init
	//myQueue->push(make_pair(xPos, yPos));

	// used to check already visited positions on the map
	/*for (int i = 0; i < _X_MAP_BOUND; i++)
		for (int j = 0; j < _Y_MAP_BOUND; j++)
			Visited[i][j] = Game::level1Map->accesMapCoordinates(i, j);*/
	
	mobDamage = mobDMG;
	this->health = health;
	heroRefference = hero;
	mobCounter++;
	mobIndex = mobCounter;
}

void Mob::update() {
	if (playerIsInVision(BASIC_MOBS_VISION)) {
		int heroX = heroRefference->getXpos();
		int heroY = heroRefference->getYpos();

		int newX = xPos;
		int newY = yPos;

		if (xPos <= heroX) {
			newX++;
		}
		if (xPos >= heroX) {
			newX--;
		}
		if (yPos >= heroY) {
			newY--;
		}
		if (yPos <= heroY) {
			newY++;
		}


		if (Game::levelMap->Collision(newX, newY) != true) {
			xPos = newX;
			yPos = newY;
			destinationRectangle.x = newX * SCALESIZE;
			destinationRectangle.y = newY * SCALESIZE;
		}
	}
}

/*bool Mob::raceCondition(const int givenRow, const int givenColumn) {
	for (auto it = Game::arrayOfCoordinatesForMobs.begin(); it != Game::arrayOfCoordinatesForMobs.end(); it++) {
		if (givenRow == it->first and givenColumn == it->second)
			return true;
	}
	return false;
}

*/

/*void Mob::update() {
	bool firstToBeProccessed = false;

	if (!myQueue->empty()) {
		int i = myQueue->front().first;
		int j = myQueue->front().second;
		Game::arrayOfCoordinatesForMobs[mobIndex] = make_pair(i, j);
		xPos = Game::arrayOfCoordinatesForMobs[mobIndex].first; // current mob position
		yPos = Game::arrayOfCoordinatesForMobs[mobIndex].second;
		myQueue->pop();

		// ! we also should draw the current mob
		// there is also an issue regarding the movement of the other mobs in the meantime
		// we could have another mob at the current position at the moment of speaking

		for (int dir = 0; dir < 4; dir++) {
			int newRow = i + dirX[dir];
			int newColumn = j + dirY[dir];

			// m am gandit sa am un visited pentru fiecare mob in partw
			// la race condition m am gandit sa tin un vector cu toate pozitiile curente ale 
			// mobilor si la fiecare if sa verific sa nu se suprapuna intre ei
			if (
				false == raceCondition(newRow, newColumn) and
				true == Map::insideBoundaries(newRow, newColumn) and
				0 < Game::level1Map->accesMapCoordinates(newRow, newColumn) and
				VISITED != this->Visited[newColumn][newRow]
				) {
				
				// ! here we will also draw, because this position is valid
				// we will draw i and j positions for the moment
				this->Visited[newColumn][newRow] = VISITED;
				myQueue->push(make_pair(newRow, newColumn));
			}
		}
	}
}

*/

/*void Mob::resetLee(const int newRow, const int newColumn) {
	this->myQueue = new queue <pair<int, int>>();

	for (int i = 0; i < _X_MAP_BOUND; i++)
		for (int j = 0; j < _Y_MAP_BOUND; j++)
			Visited[i][j] = Game::level1Map->accesMapCoordinates(newRow, newColumn);

	Visited[this->xPos][this->yPos] = VISITED;
	myQueue->push(make_pair(this->xPos, this->yPos));
}
*/

bool Mob::playerIsInVision(int givenDistance) {
	int playerX = heroRefference->getXpos();
	int playerY = heroRefference->getYpos();
	int dx = abs(playerX - this->xPos);
	int dy = abs(playerY - this->yPos);
	bool inVision = sqrt(dx * dx + dy * dy) <= givenDistance;
	return inVision;
}