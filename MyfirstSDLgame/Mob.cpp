#include "Mob.h"

Mob::Mob(const char* filePath, int xPos, int yPos, int health, Component* hero, int mobDMG) : Component(filePath, xPos, yPos, health) {
	mobDamage = mobDMG;
	this->health = health;
	heroRefference = hero;
	mobCounter++;
	mobIndex = mobCounter;
}

void Mob::update() {
	int newX = xPos, newY = yPos;

	if (playerIsInVision(BASIC_MOBS_VISION)) {
		int heroX = heroRefference->getXpos();
		int heroY = heroRefference->getYpos();

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
	}

	if (Game::levelMap->Collision(newX, newY) != true) {
		xPos = newX;
		yPos = newY;
		destinationRectangle.x = newX * SCALESIZE;
		destinationRectangle.y = newY * SCALESIZE;
	}

}

bool Mob::playerIsInVision(int givenDistance) {
	int playerX = heroRefference->getXpos();
	int playerY = heroRefference->getYpos();
	int dx = abs(playerX - this->xPos);
	int dy = abs(playerY - this->yPos);
	bool inVision = sqrt(dx * dx + dy * dy) <= givenDistance;
	return inVision;
}