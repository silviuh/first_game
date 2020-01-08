#pragma once
#include "gameHandler.h"

class LevelManager{
private:
	vector< pair<int, int> > numberOfCoinsRequiered;
	int currentLevel;
	int totalScore;
	int currentLevelheroScore;
	Game* gameHandlerReference;

public:

	bool endGameWithVictoryFlag;
	LevelManager(Game* gameHandler);
	~LevelManager();
	

	void getCurrentScoreOnLevelSucces(int score) {
		totalScore += score;
		currentLevelheroScore = score;
	}

	Game* loadNextLevel();
	bool permissionForNextLevel[2];
	void resetCurrentLevel() {
		currentLevel = LEVEL_1;
	}

	static void levelLoadScreen(int currentLevel);

	void loadFinalScreen();

};

