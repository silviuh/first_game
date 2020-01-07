#include "UpgradedMobs.h"



UpgradedMobs::UpgradedMobs(const char* filePath, int xPos, int yPos, int health, Component* hero, int mobDMG) : Mob(filePath, xPos, yPos, health, hero, mobDMG)
{
}


UpgradedMobs::~UpgradedMobs()
{
}


void UpgradedMobs::update() {
	if (playerIsInVision(UPGRADED_MOBS_VISION)) {
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