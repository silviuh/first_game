#include "Hero.h"

void Hero::update() {
	bool didNotMove = false;
	
	this->direction = Game::heroDirection; 
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
		destinationRectangle.y = this->yPos * SCALESIZE;
		destinationRectangle.x = this->xPos * SCALESIZE;
		break;
	}

	if (Game::levelMap->Collision(tempX, tempY) != true) {
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
}


void Hero::increaseScore(int number) {
	score += number;
}

void Hero::decreaseHealth(int damage) {
	health -= damage;
}