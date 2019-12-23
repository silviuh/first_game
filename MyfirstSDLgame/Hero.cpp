#include "Hero.h"

//void Hero::update() {
//	this->direction = Game::heroDirection; // heroDirection is updated in game::handleEvents
//	int tempX = this->xPos, tempY = this->yPos;
//
//	switch (this->direction) {
//	case NORTH:
//		tempY -= SCALESIZE;
//		break;
//	case EAST:
//		tempX += SCALESIZE;
//		break;
//	case SOUTH:
//		tempY += SCALESIZE;
//		break;
//	case WEST:
//		tempX -= SCALESIZE;
//		break;
//	}
//
//	sourceRectangle.x = xPos;
//	sourceRectangle.y = yPos;
//	
//	destinationRectangle.x = tempX;
//	destinationRectangle.y = tempY;
//	
//
//	int MapX = tempX / SCALESIZE;
//	int MapY = tempY / SCALESIZE;
//
//	if (Game::level1Map->Collision(sourceRectangle, destinationRectangle, MapX, MapY) != true) {
//		switch (this->direction) {
//		case NORTH:
//			this->yPos = tempY;
//			destinationRectangle.y = this->yPos;
//			break;
//		case EAST:
//			this->xPos = tempX;
//			destinationRectangle.x = this->xPos;
//			break;
//		case SOUTH:
//			this->yPos = tempY;
//			destinationRectangle.y = this->yPos;
//			break;
//		case WEST:
//			this->xPos = tempX;
//			destinationRectangle.x = this->xPos;
//			break;
//		default:
//			destinationRectangle.x = this->xPos;
//			destinationRectangle.y = this->yPos;
//			break;
//		}
//	}
//
//	//!
//	sourceRectangle.x = 0;
//	sourceRectangle.y = 0;
//	//}
//}
//






void Hero::update() {
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
	}


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
}