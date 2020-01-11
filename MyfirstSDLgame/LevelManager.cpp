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
	endGameWithVictoryFlag = false;
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
		gameHandlerReference->init((char*) "IN DIRE NEED FOR SOME COIN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false, LEVEL_2);
		gameHandlerReference->setCharacter(currentCharacterInGame);
		Game::heroDirection = UNSET;
		gameHandlerReference->createHeroes();
		succes = true;

		int timer = 500;
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
		gameHandlerReference->init((char*) "IN DIRE NEED FOR SOME COIN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false, LEVEL_3);
		gameHandlerReference->setCharacter(currentCharacterInGame);
		Game::heroDirection = UNSET;
		gameHandlerReference->createHeroes();
		succes = true;

		int timer = 500;
		while (timer) {
			LevelManager::levelLoadScreen(currentLevel);
			timer--;
		}
		break;
	}

	case LEVEL_3: {
		int timer = 500;
		while (timer) {
			LevelManager::loadFinalScreen();
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
	if (nullptr == font)
		LOG_ERROR("TTF_OpenFont failed", 83);

	string text = "LEVEL " + to_string(currentLevel) + " Loading ...";

	SDL_Rect blittingRectangle;
	blittingRectangle.x = 100;
	blittingRectangle.y = 160;
	blittingRectangle.h = 150;
	blittingRectangle.w = 600;

	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), SDL_Color({ 148,0,211 }), 350);
	if (nullptr == textSurface)
		LOG_ERROR("TTF_RenderText_Blended_Wrapped failed", 97);

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	if (nullptr == textTexture)
		LOG_ERROR("SDL_CreateTextureFromSurface failed", 99);

	SDL_RenderCopy(Game::renderer, textTexture, nullptr, &blittingRectangle);

	SDL_RenderPresent(Game::renderer);
	SDL_FreeSurface(textSurface);
}


void LevelManager::loadFinalScreen() {
	int total = (NUMBER_OF_GOLD_COINS_LEVEL1 + NUMBER_OF_GOLD_COINS_LEVEL2 + NUMBER_OF_GOLD_COINS_LEVEL3) * GOLD_COIN_SCORE_INCREASE;
	
	SDL_RenderClear(Game::renderer);
	TTF_Font *font = TTF_OpenFont(ARCHERY_BLACK, 20);
	if (nullptr == font)
		LOG_ERROR("TTF_OpenFont failed", 114);

	string text = "YOU HAVE WON THE GAME! CONGRATULATIONS. FINAL SCORE IS: " + to_string(total);

	SDL_Rect blittingRectangle;
	blittingRectangle.x = 100;
	blittingRectangle.y = 160;
	blittingRectangle.h = 150;
	blittingRectangle.w = 600;

	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), SDL_Color({ 148,0,211 }), 350);
	if (nullptr == textSurface)
		LOG_ERROR("TTF_RenderText_Blended_Wrapped failed", 126);

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	if (nullptr == textTexture)
		LOG_ERROR("SDL_CreateTextureFromSurface failed", 130);

	SDL_RenderCopy(Game::renderer, textTexture, nullptr, &blittingRectangle);

	SDL_RenderPresent(Game::renderer);
	SDL_FreeSurface(textSurface);

	endGameWithVictoryFlag = true;
}