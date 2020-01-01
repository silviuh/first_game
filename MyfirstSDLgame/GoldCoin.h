#pragma once
#include "Component.h"

class GoldCoin : public Component {
private:


public:
	GoldCoin(const char* imgToLoad, int xPos, int yPos);
	~GoldCoin() override;
	void update() override;
	void resetLee(const int, const int) override {}


	SDL_Texture* returnTexture() {
		return this->objTexture;
	}

	SDL_Rect returnSourceRect() {
		return this->sourceRectangle;
	}

	SDL_Rect returnDestinationRectangle() {
		return this->destinationRectangle;
	}
};