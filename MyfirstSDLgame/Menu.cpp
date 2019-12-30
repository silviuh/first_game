#include "Menu.h"

Menu::Menu(int width, int height, point location, const std::vector<menuItem> &options) {
	menuWidth = width;
	menuHeight = height;
	menuLocation = location;
	items = options;
	currentItem = 0;

	TTF_Init();
	font = TTF_OpenFont("DOTMATRI.ttf", 20);
	textColor.r = 255;
	textColor.g = 0;
	textColor.b = 0;

	cursor.x = menuLocation.first + 5;
	cursor.y = menuLocation.second + 10;
	cursor.h = 20;
	cursor.w = 10;
}

Menu::~Menu() {
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
	TTF_Quit();
}

void Menu::moveUp() {
	if (currentItem == 0) {
		currentItem = items.size() - 1;
		cursor.y += (items.size() - 1) * 20;
	}
	else {
		cursor.y -= 20;
		currentItem--;
	}
}

void Menu::moveDown() {
	if (currentItem == items.size() - 1) {
		currentItem = 0;
		cursor.y -= (items.size() - 1) * 20;
	}
	else {
		cursor.y += 20;
		currentItem++;
	}
}


// !
void Menu::drawMenu() {
	SDL_Rect rect;
	rect.x = menuLocation.first;
	rect.y = menuLocation.second;
	rect.h = menuHeight;
	rect.w = menuWidth;

	SDL_Rect rect2;
	rect2.x = menuLocation.first - 2;
	rect2.y = menuLocation.second - 2;
	rect2.h = menuHeight - 2;
	rect2.w = menuWidth - 2;

	point textPos;
	textPos.first = rect.x + 20;
	textPos.second = rect.y + 10;

	for (unsigned int i = 0; i < items.size(); i++){
		textSurface = TTF_RenderText_Solid(font, items.at(i).text.c_str(), textColor);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);

		textureManager::Draw(textTexture, rect, rect2);
		textPos.second += 20;
		SDL_FreeSurface(textSurface);
	}
}


void Menu::selectCurrentItem() {
	// later complete this with start game, instructions, exit.
	items[currentItem].optionFunction();
}

