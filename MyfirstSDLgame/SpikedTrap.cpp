#include "SpikedTrap.h"



SpikedTrap ::SpikedTrap(const char* imgToLoad, int xPos, int yPos) : Trap(imgToLoad, xPos, yPos, 0) {
	//destinationRectangle.y = xPos * SCALESIZE;
	//destinationRectangle.x = yPos * SCALESIZE;

	destinationRectangle.x = xPos * SCALESIZE;
	destinationRectangle.y = yPos * SCALESIZE;
}
SpikedTrap::~SpikedTrap()
{
}
