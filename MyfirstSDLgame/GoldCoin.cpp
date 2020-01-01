#include "GoldCoin.h"

GoldCoin::GoldCoin(const char* imgToLoad, int xPos, int yPos) : Component(imgToLoad, xPos, yPos, 0) {
	destinationRectangle.x = xPos * SCALESIZE;
	destinationRectangle.y = yPos * SCALESIZE;
}

GoldCoin::~GoldCoin() {


}

void GoldCoin::update() {


}
