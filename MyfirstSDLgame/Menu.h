#pragma once
#include "gameHandler.h"
#include "TextureManager.h"

typedef void(*function)();
typedef pair<int, int> point;
class menuItem;

class Menu {
protected:
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
	int optionsFlag;
	bool showMessageWhenPlayerDies;

	Menu(int width, int height, point location, const std::vector<menuItem> &options);
	~Menu();
	virtual void moveUp();
	virtual void moveDown();
	virtual void drawMenu();
	virtual void selectCurrentItem();
	virtual void handleEvents();

	void setInstruction(int offsetInMenu, function);

	void switchOffMenuLoop() {
		MenuIsActive = false;
	}

	void switchOnMenuLoop() {
		MenuIsActive = true;
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

	virtual string getSelectedCharacter() {
		return string("unset");
	}

	virtual void characterDataInit() {

	}
};


struct menuItem {
	string text;
	function optionFunction;
};
