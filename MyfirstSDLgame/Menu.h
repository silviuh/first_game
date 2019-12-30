#pragma once
#include "gameHandler.h"
#include "TextureManager.h"

typedef void(*function)();
typedef pair<int, int> point;

class Menu {
private:
	int menuWidth;
	int menuHeight;
	point menuLocation;
	std::vector<menuItem> items;
	int currentItem;
	TTF_Font *font;
	SDL_Color textColor;
	SDL_Surface *textSurface;
	SDL_Rect cursor;

public:
	Menu(int width, int height, point location, const std::vector<menuItem> &options);
	~Menu();
	void moveUp();
	void moveDown();
	void drawMenu();
	void selectCurrentItem();
};


struct menuItem {
	string text;
	function optionFunction;
};
