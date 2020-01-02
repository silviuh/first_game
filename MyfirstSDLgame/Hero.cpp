#include "Hero.h"
//#include "Mob.h"
// function used to update the current position of the hero
// hero moves with user input
void Hero::update() {
	bool didNotMove = false;
	// those are relative not absolut coordinates
	this->direction = Game::heroDirection; // heroDirection is updated in game::handleEvents
	int tempX = this->xPos, tempY = this->yPos;

	switch (this->direction) {
	case NORTH:
		tempY -= 1;
		break;
	case EAST:
		tempX += 1;
		break;
	case SOUTH:
		tempY += 1;
		break;
	case WEST:
		tempX -= 1;
		break;
	case UNSET:
		didNotMove = true;
		break;
	}

	// used for establishing x and y for destionation rectangle
	// in order to be rendered
	if (Game::level1Map->Collision(tempX, tempY) != true) {
		switch (this->direction) {
		case NORTH:
			this->yPos = tempY;
			destinationRectangle.y = this->yPos * SCALESIZE;
			break;
		case EAST:
			this->xPos = tempX;
			destinationRectangle.x = this->xPos * SCALESIZE;
			break;
		case SOUTH:
			this->yPos = tempY;
			destinationRectangle.y = this->yPos * SCALESIZE;
			break;
		case WEST:
			this->xPos = tempX;
			destinationRectangle.x = this->xPos * SCALESIZE;
			break;
		default:
			destinationRectangle.x = this->xPos * SCALESIZE;
			destinationRectangle.y = this->yPos * SCALESIZE;
			break;
		}
	}
	
	/*int lenght = sizeof(Game::arrayOfMobs) / sizeof(void*);
	vector<Component*>::iterator mobIterator;

	// !
	for (mobIterator = Game::arrayOfMobs.begin(); mobIterator != Game::arrayOfMobs.end() ; mobIterator++) {
		if (didNotMove == true)
			(*mobIterator)->update();
		else
			(*mobIterator)->resetLee(0, 0);
	}
	*/
}


void Hero::increaseScore(int number) {
	score += number;
}

void Hero::decreaseHealth(int damage) {
	health -= damage;
}