#pragma once
#include "gameHandler.h"
#include "TextureManager.h"

typedef void(*function)();
typedef pair<int, int> point;
class menuItem;

class Menu {
private:
	int menuWidth;
	int menuHeight;
	point menuLocation;
	vector<menuItem> items;
	int currentItem;
	bool MenuIsActive;
	bool instructionsMenuIsActive;
	bool requestForExitingTheGame;

	TTF_Font *font;
	SDL_Color textColor[2];
	SDL_Surface *textSurface;
	SDL_Rect cursor;


public:
	Menu(int width, int height, point location, const std::vector<menuItem> &options);
	~Menu();
	void moveUp();
	void moveDown();
	void drawMenu();
	void selectCurrentItem();
	void handleEvents();

	void setInstruction(int offsetInMenu, function);
	void switchOffMenuLoop() {
		MenuIsActive = false;
	}
	void switchOnInstructionMenu() {
		instructionsMenuIsActive = true;
	}
	void switchOffInstructionMenu() {
		instructionsMenuIsActive = false;
	}

	bool menuIsActive() {
		return MenuIsActive;
	}
	bool checkIfinstructionsMenuIsActive() {
		return instructionsMenuIsActive;
	}

	bool returnRequestForExitingTheGame() {
		return requestForExitingTheGame;
	}

	void gameExit() {
		requestForExitingTheGame = true;
	}
};


struct menuItem {
	string text;
	function optionFunction;
};
