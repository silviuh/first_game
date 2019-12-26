#include "Mob.h"

//void Mob::inactiveUpdate()  {
//	// move to north direction
//	yPos += motionFlag * 1;
//	destinationRectangle.y = yPos * SCALESIZE;
//	destinationRectangle.x = xPos * SCALESIZE;
//	motionFlag = -motionFlag;
//}

void Mob::update() {
	// we will use the lee algo
	queue <pair<int, int>> myQueue;
	visitedMap[this->xPos][this->yPos] = VISITED;
	myQueue.push(make_pair(this->xPos, this->yPos));

	while (!myQueue.empty()) {
		int i = myQueue.front().first;
		int j = myQueue.front().second;
		myQueue.pop();
		for (int dir = 0; dir < 4; dir++) {
			int newRow = i + dirX[dir];
			int newColumn = j + dirY[dir];

			// m am gandit sa am un visited pentru fiecare mob in partw
			// la race condition m am gandit sa tin un vector cu toate pozitiile curente ale 
			// mobilor si la fiecare if sa verific sa nu se suprapuna intre ei
			if (
				false == raceCondition(mobCoordinates, newRow, newColumn) and
				true == insideBoundaries(newRow, newColumn) and
				Game::level1Map[newColumn][newRow] > 0 and
				VISITED != this->Visited[newColumn][newRow]
				) {

				this->Visited[newColumn][newRow] = VISITED;
				myQueue.push(make_pair(newRow, newColumn));
			}
	}

}

// un comment pt git