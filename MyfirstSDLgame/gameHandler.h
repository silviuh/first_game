#pragma once
#include "Utils.h"
#include <SDL.h>
#include "SDL_ttf.h"
#undef main

#include <SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <utility>
#include <queue>
#include <utility>
//#include "Hero.h"




using namespace std;

class Component;
class Mob;
class Map;
class Menu;

class Game {
private:
	Component *mainPlayer;
	Component *mob1;
	const Uint8* keyStates;
	int gameHandler;

	bool isRunning;
	SDL_Window *window;

	int updateCounter;

public:
	Game();
	~Game();

	int init(char* gameTitle, int xpos, int ypos, int width, int height, bool fullScreen);
	//void initObjects();
	void handleEvents();
	void update();
	int render();
	int clean();
	bool gameIsRunning() { return isRunning; }
	void logErrorHandlerFile(int, FILE* fileLogger);
	void exitGame();


	void switchOffGameLoop() {
		isRunning = false;
	}

	void switchOnGameLoop() {
		isRunning = true;
	}
	// used between translation units
	static SDL_Renderer *renderer;
	static int heroDirection;
	static Map* level1Map;
	static Menu* gameMenu;

	
	//static void initMenu();
	//static vector<Component*> arrayOfMobs;
	//static vector<pair<int, int>> arrayOfCoordinatesForMobs;
};