#include "CharacterMenu.h"


void CharacterMenu::moveUp() {
	if (currentItem == 0) {
		currentItem = charDataArray.size() - 1;
		cursor.y += (charDataArray.size() - 1) * 70;
	}
	else {
		cursor.y -= 70;
		currentItem--;
	}
}

void CharacterMenu::moveDown() {
	if (currentItem == charDataArray.size() - 1) {
		currentItem = 0;
		cursor.y -= (charDataArray.size() - 1) * 70;
	}
	else {
		cursor.y += 70;
		currentItem++;
	}
}


void CharacterMenu::drawMenu() {
	TTF_Font* tahoma = TTF_OpenFont(TAHOMA, 20);
	TTF_Font* archery_black = TTF_OpenFont(ARCHERY_BLACK, 20);
	SDL_Rect blittingRectangleHero, blittingRectangleText;
	blittingRectangleHero.x = 300;
	blittingRectangleHero.y = 60;
	blittingRectangleHero.h = 100;
	blittingRectangleHero.w = 150;

	blittingRectangleText.x = 25;
	blittingRectangleText.y = 160;
	blittingRectangleText.h = 100;
	blittingRectangleText.w = 750;

	SDL_RenderClear(Game::renderer);
	SDL_Texture* pngTexture = nullptr;


	for (unsigned int i = 0; i < charDataArray.size(); i++) {
		if (i == currentItem) {
			pngTexture = textureManager::loadTexture(charDataArray.at(i).characterSelectedPNG.c_str());
			textSurface = TTF_RenderText_Solid(font, charDataArray.at(i).characterAbilityInfo.c_str(), textColor[1]);
			SDL_RenderCopy(Game::renderer, pngTexture, nullptr, &blittingRectangleHero);
		}
		else {
			pngTexture = textureManager::loadTexture(charDataArray.at(i).characterPNG.c_str());
			SDL_RenderCopy(Game::renderer, pngTexture, nullptr, &blittingRectangleHero);
			textSurface = TTF_RenderText_Solid(font, charDataArray.at(i).characterAbilityInfo.c_str(), textColor[0]);
		}
			
		/*SDL_Surface * textSurface = TTF_RenderText_Blended_Wrapped(archery_black, charDataArray.at(i).characterAbilityInfo.c_str(), SDL_Color({ 139,0,139 }), 350);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
		SDL_FreeSurface(textSurface);
		SDL_RenderCopy(Game::renderer, textTexture, nullptr, &blittingRectangle);*/

		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
		SDL_RenderCopy(Game::renderer, textTexture, nullptr, &blittingRectangleText);
		SDL_FreeSurface(textSurface);

		blittingRectangleText.y += 250;
		blittingRectangleHero.y += 250;

		SDL_DestroyTexture(pngTexture);
		SDL_DestroyTexture(textTexture);
	}
	SDL_RenderPresent(Game::renderer);
}



void CharacterMenu::selectCurrentItem()  {
	MenuIsActive = false;
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
			requestForExitingTheGame = true;
			MenuIsActive = false;
			break;
		}
		}
	}
}

CharacterMenu::~CharacterMenu()
{
}
