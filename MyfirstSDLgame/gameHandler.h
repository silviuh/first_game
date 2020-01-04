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
#include <time.h>   

#include <fstream>
//#include "Hero.h"



using namespace std;

class Component;
class Mob;
class Hero;
class Map;
class Menu;
class GoldCoin;
class SpikedTrap;

class Game {
private:
	Component *mainPlayer;
	Component *mob1;
	vector <GoldCoin*> GoldCoinArray;
	vector <SpikedTrap*> SpikedTrapArray;
	string currentMapPath;
	int numberOfGoldCoins;
	const Uint8* keyStates;
	int gameHandler;

	bool isRunning;
	SDL_Window *window;

	int updateCounter;

public:
	Game(const int goldCoins, string mapPath);
	~Game();

	int init(char* gameTitle, int xpos, int ypos, int width, int height, bool fullScreen, const int GoldCoins, int currentLevelInGame);
	//void initObjects();
	void handleEvents();
	void update();
	pair<int, int> render();
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

	int currentLevel;

	static SDL_Renderer *renderer;
	static int heroDirection;
	static Map* level1Map;
	static Menu* gameMenu;

	static pair<int, int> generateRandomCoordinates(Component* hero);
	static pair<int, int> returnHeroCoordinates(Component* hero);
	static void coinsManager(vector <GoldCoin*> &, const int heroX, const int heroY, Component& mainPlayer);
	static void trapsManager(vector <SpikedTrap*> &, const int heroX, const int heroY, Component& mainPlayer);
	static void renderScore(const int currentScore);
	static void renderLife(const int currentLife);
	static void renderCurrentLevelNumber(const int currentLevel);
	static bool healthManager(Component& mainPlayer);



	//static void initMenu();
	//static vector<Component*> arrayOfMobs;
	//static vector<pair<int, int>> arrayOfCoordinatesForMobs;
};