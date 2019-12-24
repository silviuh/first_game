#include "Mob.h"

void Mob::update()  {
	// move to north direction
	yPos += motionFlag * 1;
	destinationRectangle.y = yPos * SCALESIZE;
	destinationRectangle.x = xPos * SCALESIZE;
	motionFlag = -motionFlag;
}

// un comment pt git