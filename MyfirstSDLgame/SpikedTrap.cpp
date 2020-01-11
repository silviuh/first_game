#include "SpikedTrap.h"



SpikedTrap ::SpikedTrap(const char* imgToLoad, int xPos, int yPos) : Trap(imgToLoad, xPos, yPos, 0) {
	destinationRectangle.x = xPos * SCALESIZE;
	destinationRectangle.y = yPos * SCALESIZE;
}
SpikedTrap::~SpikedTrap()
{
}
