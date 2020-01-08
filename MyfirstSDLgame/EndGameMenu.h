#pragma once
#include "Menu.h"

class EndGameMenu : public Menu{
private:
	int mainPlayerScore;
	int currentLevel;


public:

	EndGameMenu(int width, int height, point location, const std::vector<menuItem> &options, const int PlayerScore, const int levelReached) :
		Menu(width, height, location, options) {
		mainPlayerScore = PlayerScore;
		currentLevel = levelReached;
		showMessageWhenPlayerDies = false;
	}
	void drawMenu() override;

	~EndGameMenu(){}
};
