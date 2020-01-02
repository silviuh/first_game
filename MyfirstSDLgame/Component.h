#pragma once
#include "gameHandler.h"
#include "Utils.h"

//class gameHandler;
class Component {
protected:
	int xPos, yPos;
	int velocity;
	int health;
	SDL_Texture* objTexture;
	SDL_Rect sourceRectangle, destinationRectangle;
	int direction;

public:

	int getXpos() const {
		return xPos;
	}
	int getYpos() const {
		return yPos;
	}

	SDL_Texture* getTexture() const {
		return objTexture;
	}
	SDL_Rect getSrcRect() const {
		return sourceRectangle;
	}
	SDL_Rect getDestRect() const {
		return destinationRectangle;
	}

	virtual int getCurrentScore() {
		return UNDEFINED_SCORE;
	}

	// xPos and yPos will be random at the begging of the level (apart from the hero)
	Component(const char* imageToLoad, int xPos = 0, int yPos = 0, int health = 100);
	virtual ~Component() = 0;
	virtual void update() = 0;
	void render();
	virtual void resetLee(const int, const int) = 0;
	virtual void increaseScore(int number) {}
	virtual void decreaseHealth(int damage) {}
};