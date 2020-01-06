#include "LevelManager.h"



LevelManager::LevelManager(Game* gameHandler){
	this->currentLevelheroScore = 0;
	currentLevel = LEVEL_1;

	numberOfCoinsRequiered.push_back( make_pair(LEVEL_1, GOLD_COINS_LEVEL1) );
	numberOfCoinsRequiered.push_back(make_pair(LEVEL_2, GOLD_COINS_LEVEL2) );
	numberOfCoinsRequiered.push_back(make_pair(LEVEL_3, GOLD_COINS_LEVEL3) );

	permissionForNextLevel[LEVEL_1] = false;
	permissionForNextLevel[LEVEL_2] = false;
	permissionForNextLevel[LEVEL_3] = false;

	gameHandlerReference = gameHandler;
}


Game* LevelManager::loadNextLevel() {
	bool succes = false;

	switch (currentLevel) {
	case LEVEL_1: {
		permissionForNextLevel[LEVEL_1 - 1] = true;
		currentLevel++;

		gameHandlerReference->clean();
		delete gameHandlerReference;
		gameHandlerReference = new Game();
		gameHandlerReference->init((char*) "IN DIRE NEED FOR SOME COIN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false, 10, LEVEL_2);
		succes = true;

		int timer = 1000;
		while (timer) {
			LevelManager::levelLoadScreen(currentLevel);
			timer--;
		}
		break;
	}

	case LEVEL_2: {
		permissionForNextLevel[LEVEL_2 - 1] = true;
		currentLevel++;

		gameHandlerReference->clean();
		delete gameHandlerReference;
		gameHandlerReference = new Game();
		gameHandlerReference->init((char*) "IN DIRE NEED FOR SOME COIN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false, 10, LEVEL_3);
		succes = true;

		int timer = 1000;
		while (timer) {
			LevelManager::levelLoadScreen(currentLevel);
			timer--;
		}
		break;
	}
}
	return gameHandlerReference;
}


void LevelManager::levelLoadScreen(int currentLevel) {
	SDL_RenderClear(Game::renderer);
	TTF_Font *font = TTF_OpenFont(ARCHERY_BLACK, 20);
	string text = "LEVEL " + to_string(currentLevel) + " Loading ...";



	SDL_Rect blittingRectangle;
	blittingRectangle.x = 100;
	blittingRectangle.y = 160;
	blittingRectangle.h = 150;
	blittingRectangle.w = 600;

	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), SDL_Color({ 148,0,211 }), 350);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	SDL_RenderCopy(Game::renderer, textTexture, nullptr, &blittingRectangle);

	SDL_RenderPresent(Game::renderer);
	SDL_FreeSurface(textSurface);
}