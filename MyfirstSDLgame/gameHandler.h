#pragma once
#include "Utils.h"
#include <SDL.h>
#undef main

#include <SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <utility>
//#include "Hero.h"



using namespace std;

class Component;
class Map;

class Game {
private:
	Component *mainPlayer;
	Component *enemy1;
	const Uint8* keyStates;
	int gameHandler;

	bool isRunning;
	SDL_Window *window;

	int updateCounter;

public:
	Game();
	~Game();

	int init(char* gameTitle, int xpos, int ypos, int width, int height, bool fullScreen);
	void initObjects();
	void handleEvents();
	void update();
	int render();
	int clean();
	bool gameIsRunning() { return isRunning; }
	void logErrorHandlerFile(int, FILE* fileLogger);



	static SDL_Renderer *renderer;
	static int heroDirection;
	static Map* level1Map;
};