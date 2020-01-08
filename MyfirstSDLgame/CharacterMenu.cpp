#include "CharacterMenu.h"


void CharacterMenu::moveUp() {
	if (currentItem == 0) {
		currentItem = items.size() - 1;
		cursor.y += (items.size() - 1) * 70;
	}
	else {
		cursor.y -= 70;
		currentItem--;
	}
}

void CharacterMenu::moveDown() {
	if (currentItem == items.size() - 1) {
		currentItem = 0;
		cursor.y -= (items.size() - 1) * 70;
	}
	else {
		cursor.y += 70;
		currentItem++;
	}
}


void CharacterMenu::drawMenu() {
	SDL_Rect blittingRectangle;
	blittingRectangle.x = 300;
	blittingRectangle.y = 200;
	blittingRectangle.h = 100;
	blittingRectangle.w = 250;

	SDL_RenderClear(Game::renderer);
	SDL_Texture* pngTexture = nullptr;
	SDL_Texture* textTexture = nullptr;



	for (unsigned int i = 0; i < items.size(); i++) {
		if (i == currentItem) {
			pngTexture = textureManager::loadTexture(charDataArray.at(i).characterSelectedPNG.c_str());
			SDL_RenderCopy(Game::renderer, pngTexture, nullptr, &blittingRectangle);

			blittingRectangle.y += 40;
			
			pngTexture = textureManager::loadTexture(charDataArray.at(i).characterAbilityInfo.c_str());
			SDL_RenderCopy(Game::renderer, textTexture, nullptr, &blittingRectangle);
		}
		else {
			pngTexture = textureManager::loadTexture(charDataArray.at(i).characterPNG.c_str());
			SDL_RenderCopy(Game::renderer, pngTexture, nullptr, &blittingRectangle);

			blittingRectangle.y += 40;

			pngTexture = textureManager::loadTexture(charDataArray.at(i).characterAbilityInfo.c_str());
			SDL_RenderCopy(Game::renderer, textTexture, nullptr, &blittingRectangle);
		}
		

		blittingRectangle.y += 100;
		SDL_DestroyTexture(pngTexture);
		SDL_DestroyTexture(textTexture);
	}

	SDL_RenderPresent(Game::renderer);
}



void CharacterMenu::selectCurrentItem()  {
	selectedCharacter = charDataArray.at(currentItem).characterClassName;
}


void CharacterMenu::handleEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN: {
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				moveUp();
				break;
			case SDLK_DOWN:
				moveDown();
				break;
			case SDLK_RETURN:
				selectCurrentItem();
				break;
			}
			break;
		}
		case SDL_QUIT: {
			MenuIsActive = false;
			break;
		}
		}
	}
}

CharacterMenu::~CharacterMenu()
{
}
