#include "EndGameMenu.h"


void EndGameMenu::drawMenu() {
	TTF_Font* tahoma = TTF_OpenFont(TAHOMA, 20);
	TTF_Font* archery_black = TTF_OpenFont(ARCHERY_BLACK, 20);
	SDL_Rect blittingRectangle;
	vector<string> textArray;

	textArray.push_back((string) "YOU ARE DEAD!");
	textArray.push_back((string)("YOUR FINAL SCORE IS: " + to_string(mainPlayerScore)));
	textArray.push_back((string) "CURRENT LEVEL REACHED: " + to_string(currentLevel));

	blittingRectangle.x = 230;
	blittingRectangle.y = 15;
	blittingRectangle.h = 64;
	blittingRectangle.w = 300;
		
	SDL_RenderClear(Game::renderer);

	for (int i = 0; i < textArray.size(); i++) {
		SDL_Surface * textSurface = TTF_RenderText_Blended_Wrapped(archery_black, textArray.at(i).c_str(), SDL_Color({ 139,0,139 }), 350);			SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
		SDL_FreeSurface(textSurface);
		SDL_RenderCopy(Game::renderer, textTexture, nullptr, &blittingRectangle);
		blittingRectangle.y += 70;
	}

	blittingRectangle.y += 70;

	for (unsigned int i = 0; i < items.size(); i++) {
		if (i == currentItem)
			textSurface = TTF_RenderText_Solid(font, items.at(i).text.c_str(), textColor[1]);
		else
			textSurface = TTF_RenderText_Solid(font, items.at(i).text.c_str(), textColor[0]);

		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
		SDL_RenderCopy(Game::renderer, textTexture, nullptr, &blittingRectangle);
		blittingRectangle.y += 70;
		SDL_FreeSurface(textSurface);
	}

	SDL_RenderPresent(Game::renderer);
}
