#pragma once
#include "gameHandler.h"
#include "Menu.h"
#include "Utils.h"
#include "Hero.h"
#include "Mob.h"
#include "TextureManager.h"
#include "Map.h"


Menu* Game::gameMenu = nullptr;

SDL_Renderer* Game::renderer = nullptr;
int Game::heroDirection = UNSET;
Map* Game::level1Map = nullptr;
//vector<Component*> arrayOfMobs;
//vector<pair<int, int>> arrayOfCoordinatesForMobs;
int Mob::mobCounter = 0;

Game ::Game() {
	this->isRunning = false;
	this->window = nullptr;
}

Game::~Game() {

}

int Game::init(char* gameTitle, int xpos, int ypos, int width, int height, bool fullScreen) {
	int flags = false;
	fullScreen ? flags = SDL_WINDOW_FULLSCREEN : flags = false;

	if (false == SDL_Init(SDL_INIT_EVERYTHING)) {
		cout << "Subsystems Initialized...";
		this->window = SDL_CreateWindow(gameTitle, xpos, ypos, width, height, flags);

		if (false == window) 
			return _sdlCreateWindow;
		
		
		SDL_Renderer* asd = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		renderer = asd;
		

		SDL_Surface* tempSurface = IMG_Load(DIRT1_PICTURE);
		if (NULL == tempSurface) {
			return NULL;
		}
		// rendererPtr = &asd;
		SDL_Texture* myTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);

		if (false == renderer)
			return _sdlCreateRenderer;
		else {
			int flag = SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			if (false != flag)
				return _SDL_SetRenderDrawColor;
		}
		
		this->isRunning = true;
	}
	else 
		return _windowInitEverything;

	
	/*playerTexture = textureManager::loadTexture("C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\mainCharProfile.png.png", this->renderer);
	if (NULL == playerTexture) {
		return _SDL_CreateTextureFromSurface;
	}*/
	level1Map = new Map();
	level1Map->LoadMap(lv1);
	mainPlayer = new Hero("C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\mainCharProfile.png.png", 2, 2, 100);
	// !
	/*arrayOfMobs.push_back(new Mob("C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\mob01.png", 5, 5, 100));
	arrayOfMobs.push_back(new Mob("C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\mob01.png", 6, 5, 100));
	arrayOfMobs.push_back(new Mob("C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\mob01.png", 7, 5, 100));
	arrayOfMobs.push_back(new Mob("C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\mob01.png", 8, 5, 100));

	arrayOfCoordinatesForMobs.push_back(make_pair(5, 5));
	arrayOfCoordinatesForMobs.push_back(make_pair(6, 5));
	arrayOfCoordinatesForMobs.push_back(make_pair(7, 5));
	arrayOfCoordinatesForMobs.push_back(make_pair(8, 5));
	*/
	// !

	return _INITSUCCES;
}





void Game::handleEvents() {
	SDL_Event event;

	while(SDL_PollEvent(&event)){
		switch (event.type) {
		case SDL_QUIT: {
			this->isRunning = false;
			break;
		}

		case SDL_KEYDOWN: {
			switch (event.key.keysym.sym) {
			case SDLK_w:
				heroDirection = NORTH;
				cout << "w key pressed";
				cout << endl;
				break;
			case SDLK_d:
				heroDirection = EAST;
				cout << "d key pressed";
				cout << endl;
				break;
			case SDLK_s:
				heroDirection = SOUTH;
				cout << "1 key pressed";
				cout << endl;
			break;
			case SDLK_a:
				heroDirection = WEST;
				cout << "a key pressed";
				cout << endl;
				break;
			}
			break;
		}
		


		case SDL_KEYUP: {
		case SDLK_w:
			heroDirection = UNSET;
			cout << "w key pressed";
			cout << endl;
			break;
		case SDLK_d:
			heroDirection = UNSET;
			cout << "d key pressed";
			cout << endl;
			break;
		case SDLK_s:
			heroDirection = UNSET;
			cout << "1 key pressed";
			cout << endl;
			break;
		case SDLK_a:
			heroDirection = UNSET;
			cout << "a key pressed";
			cout << endl;
			break;
		}



		default:
			cout << "ok";
			return;

		}
	}
}




void Game::update() {
	this->updateCounter++;
	mainPlayer->update();
	//mob1->update();
	//enemy1->update();

	// ! - !
	//if (mainPlayer->Collision(*enemy1))
		//cout << endl << "au";

	// cout << endl << "Game got updated of: " << this->updateCounter << " times";
}




int Game::render() {
	if (false != SDL_RenderClear(renderer)) {
		return _SDL_RenderClear;
	}

	level1Map->DrawMap();
	mainPlayer->render();
	//mob1->render();
	//enemy1->render(this->renderer);
	SDL_RenderPresent(renderer);


	// uses the entire image, and the whole render frame
	/*if (false != SDL_RenderCopy(renderer, playerTexture, NULL, &destinationRectangle)) {
		return _SDL_RenderCopy;
	}

	SDL_RenderPresent(renderer);*/
	return _RENDERINGSUCCES;
} 




int Game::clean() {
	this->isRunning = false;

	if(NULL == this->window)
		return _SDL_DestroyWindow;
	else
		SDL_DestroyWindow(this->window);

	if (NULL == renderer)
		return _SDL_DestroyRenderer;
	else
		SDL_DestroyRenderer(renderer);

	SDL_Quit();
	return _CLEANUPSUCCES;
}




void Game::logErrorHandlerFile(int error, FILE* fileLogger) {
	switch (error) {
	case _windowFullScreen:
		// cout << endl << "";
		break;
	case _windowInitEverything:
		cout << endl << "_windowInitEverything did not work...";
		break;
	case _sdlCreateWindow:
		cout << endl << "_sdlCreateWindow did not work...";
		break;
	case _sdlCreateRenderer:
		cout << endl << "_sdlCreateRenderer did not work...";
		break;
	case _SDL_RenderClear:
		cout << endl << "_SDL_RenderClear did not work...";
		break;
	case _SDL_DestroyWindow:
		cout << endl << "_SDL_DestroyWindow did not work...";
		break;
	case _SDL_DestroyRenderer:
		cout << endl << "_SDL_DestroyRenderer did not work...";
		break;
	case _SDL_SetRenderDrawColor:
		cout << endl << "_SDL_DestroyRenderer did not work...";
		break;
	case _SDL_IMG_Load:
		cout << endl << "_SDL_IMG_Load did not work...";
		break;
	case _SDL_CreateTextureFromSurface:
		cout << endl << "_SDL_CreateTextureFromSurface did not work...";
		break;
	case _SDL_RenderCopy:
		cout << endl << "_SDL_RenderCopy did not work...";
		break;
	}
}

void Game::initMenu() {
	vector<menuItem> options;
	menuItem m1 = { "Start Game", nullptr };
	menuItem m2 = { "Instructions", nullptr };
	menuItem m3 = { "Exit", nullptr};
	options.push_back(m1);
	options.push_back(m2);
	options.push_back(m3);

	gameMenu = new Menu(250, 80, make_pair(10, 10), options);
}