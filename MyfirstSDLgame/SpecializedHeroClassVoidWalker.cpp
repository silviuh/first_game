#include "SpecializedHeroClassVoidWalker.h"


SpecializedHeroClassVoidWalker::~SpecializedHeroClassVoidWalker(){
}

void SpecializedHeroClassVoidWalker::castAbility() {
	if (abilityActivated == true and abilityCanBeCasted == true) {
		setAbilityColdown();
		abilityCanBeCasted = false;

		int xPos,  yPos;
		do {
			xPos = rand() % (_X_MAP_BOUND - 3) + 2;
			yPos = rand() % (_Y_MAP_BOUND - 3) + 2;
		} while (levelMap->accesMapCoordinates(xPos, yPos) < 0);

		this->xPos = xPos;
		this->yPos = yPos;

		/*TTF_Font* tahoma = TTF_OpenFont(ARCHERY_BLACK, 20);
		SDL_Rect blittingRectangle;
		blittingRectangle.x = xPos;
		blittingRectangle.y = yPos;
		blittingRectangle.h = SCALESIZE;
		blittingRectangle.w = SCALESIZE;
		SDL_Texture* voidHoleTexture = textureManager::loadTexture(VOID_HOLE_PNG);
		int voidHoleColdown = VOID_HOLE_COLDOWN;

		while (voidHoleColdown) {
			SDL_RenderCopy(Game::renderer, voidHoleTexture, nullptr, &blittingRectangle);
			voidHoleColdown--;
		}*/
	}
}


void SpecializedHeroClassVoidWalker::update() {
	Hero::update();
	castAbility();
	abilityActivated = false;
}