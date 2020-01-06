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
		break;
	}
}
	return gameHandlerReference;
}