#include "Menu.h"

Menu::Menu(int width, int height, point location, const std::vector<menuItem> &options) {
	menuWidth = width;
	menuHeight = height;
	menuLocation = location;
	items = options;
	currentItem = 0;

	TTF_Init();
	font = TTF_OpenFont(BALOO, 20);
	
	textColor[0] = { 204, 0, 204 };
	textColor[1] = { 255, 255, 51 };

	cursor.x = menuLocation.first + 5;
	cursor.y = menuLocation.second + 10;
	cursor.h = 20;
	cursor.w = 10;

	MenuIsActive = true;
	instructionsMenuIsActive = false;
	requestForExitingTheGame = false;
}

Menu::~Menu() {
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
	TTF_Quit();
}

void Menu::moveUp() {
	if (currentItem == 0) {
		currentItem = items.size() - 1;
		cursor.y += (items.size() - 1) * 70;
	}
	else {
		cursor.y -= 70;
		currentItem--;
	}
}

void Menu::moveDown() {
	if (currentItem == items.size() - 1) {
		currentItem = 0;
		cursor.y -= (items.size() - 1) * 70;
	}
	else {
		cursor.y += 70;
		currentItem++;
	}
}


// !
void Menu::drawMenu() {
	SDL_Rect blittingRectangle;
	blittingRectangle.x = menuLocation.first - 2;
	blittingRectangle.y = menuLocation.second - 2;
	blittingRectangle.h = 100;
	blittingRectangle.w = 250;

	SDL_RenderClear(Game::renderer);

	for (unsigned int i = 0; i < items.size(); i++){
		if(i == currentItem)
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


void Menu::selectCurrentItem() {
	// later complete this with start game, instructions, exit.
	items[currentItem].optionFunction();
}


void Menu::handleEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN: {
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				moveUp();
				break;
			case SDLK_DOWN:
				moveDown();
				break;
			case SDLK_RETURN:
				selectCurrentItem();
				break;
			}
			break;
		}
		case SDL_QUIT: {
			MenuIsActive = false;
			break;
		}
		}
	}
}


void Menu::setInstruction(int offsetInMenu, function givenFunction) {
	this->items.at(offsetInMenu).optionFunction = givenFunction;
}