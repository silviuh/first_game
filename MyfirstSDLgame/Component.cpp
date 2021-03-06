#include "Component.h"
#include "TextureManager.h"

Component::Component(const char* imageToLoad, int xPos, int yPos, int health) {
	this->xPos = xPos;
	this->yPos = yPos;
	this->health = health;
	this->objTexture = textureManager::loadTexture(imageToLoad);
	this->velocity = 32;

	sourceRectangle.h = SCALESIZE;
	sourceRectangle.w = SCALESIZE;
	destinationRectangle.w = SCALESIZE;
	destinationRectangle.h = SCALESIZE;
	destinationRectangle.x = 0;
	destinationRectangle.y = 0;
	isActive = true;
	abilityColdown = 5;
	abilityCanBeCasted = true;
}

Component::~Component() {
	this->xPos = -1;
	this->yPos = -1;
	this->health = 0;
	SDL_DestroyTexture(this->objTexture);
}

void Component::update() {
}

void Component::render() {
	if (false != SDL_RenderCopy(Game::renderer, this->objTexture, &sourceRectangle, &destinationRectangle))
		LOG_ERROR("SDL_RenderCopy failed", 33);
}

