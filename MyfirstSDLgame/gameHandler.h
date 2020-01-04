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

typedef unsigned int Level;
struct levelSpecificDataContainer;


class Game {
private:
	Component *mainPlayer;
	Component *mob1;
	vector <GoldCoin*> GoldCoinArray;
	vector <SpikedTrap*> SpikedTrapArray;
	vector <Component*> MobsArray;

	string currentMapPath;
	int numberOfGoldCoins;
	const Uint8* keyStates;
	int gameHandler;

	bool isRunning;
	SDL_Window *window;

	int updateCounter;

public:
	Game();
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
	static Map* levelMap;
	static Menu* gameMenu;


	static vector < pair<Level, levelSpecificDataContainer> > storageContainerForLevels;
	static pair<int, int> generateRandomCoordinates(Component* hero);
	static pair<int, int> returnHeroCoordinates(Component* hero);
	static void coinsManager(vector <GoldCoin*> &, const int heroX, const int heroY, Component& mainPlayer);
	static void trapsManager(vector <SpikedTrap*> &, const int heroX, const int heroY, Component& mainPlayer);
	static void mobsManager(vector <Component*> &, const int heroX, const int heroY, Component& mainPlayer, vector <SpikedTrap*> & SpikedTrapArray);

	static void renderScore(const int currentScore);
	static void renderLife(const int currentLife);
	static void renderCurrentLevelNumber(const int currentLevel);
	static void initializeStorageContainerForLevels(vector < pair<Level, levelSpecificDataContainer> > &);
	



	//static void initMenu();
	//static vector<Component*> arrayOfMobs;
	//static vector<pair<int, int>> arrayOfCoordinatesForMobs;
};

struct levelSpecificDataContainer{
	int numberOfCoins;
	int numberOfSpikedBalls;
	int numberOfMobs;
	int numberOfBasicMobs;
	int numberOfUpgradedMobs;
	string mapFilePath;
};