#pragma once
#include "gameHandler.h"
#include "Menu.h"
#include "Utils.h"
#include "Hero.h"
#include "Mob.h"
#include "GoldCoin.h"
#include "SpikedTrap.h"
#include "TextureManager.h"
#include "Map.h"


SDL_Renderer* Game::renderer = nullptr;
int Game::heroDirection = UNSET;
Map* Game::level1Map = nullptr;
//vector<Component*> arrayOfMobs;
//vector<pair<int, int>> arrayOfCoordinatesForMobs;
int Mob::mobCounter = 0;

Game ::Game(const int goldCoins, string mapPath) {
	this->isRunning = false;
	this->window = nullptr;
	numberOfGoldCoins = goldCoins;
	this->currentMapPath = mapPath;
	srand(time(NULL));
}

Game::~Game() {

}

int Game::init(char* gameTitle, int xpos, int ypos, int width, int height, bool fullScreen, const int GoldCoins, int currentLevelInGame) {
	int flags = false;
	fullScreen ? flags = SDL_WINDOW_FULLSCREEN : flags = false;

	if (false == SDL_Init(SDL_INIT_EVERYTHING)) {
		cout << "Subsystems Initialized...";
		this->window = SDL_CreateWindow(gameTitle, xpos, ypos, width, height, flags);

		if (false == window) 
			return _sdlCreateWindow;
		
		
		SDL_Renderer* asd = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		renderer = asd;
	
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

	currentLevel = currentLevelInGame;
	level1Map = new Map();
	level1Map->LoadMap(currentMapPath);
	mainPlayer = new Hero(HERO_PNG, STARTING_X_POS, STARTING_Y_POS, 100);

	for (int i = 0; i < numberOfGoldCoins; i++) {
		pair<int, int> tempPair = Game::generateRandomCoordinates(mainPlayer);
		GoldCoin* newGoldCoin = new GoldCoin(GOLD_COIN_PNG, tempPair.second, tempPair.first);
		GoldCoinArray.push_back(newGoldCoin);
	}

	for (int i = 0; i < NUMBER_OF_SPIKED_BALLS_LEVEL_1; i++) {
		pair<int, int> tempPair = Game::generateRandomCoordinates(mainPlayer);
		SpikedTrap* newSpikeyBall = new SpikedTrap(SPIKEY_BALL_PNG, tempPair.second, tempPair.first);
		SpikedTrapArray.push_back(newSpikeyBall);
	}
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
	Game::coinsManager(GoldCoinArray, mainPlayer->getXpos(), mainPlayer->getYpos(), *mainPlayer);
	Game::trapsManager(SpikedTrapArray, mainPlayer->getXpos(), mainPlayer->getYpos(), *mainPlayer);


	//mob1->update();
	//enemy1->update();

	// ! - !
	//if (mainPlayer->Collision(*enemy1))
		//cout << endl << "au";

	// cout << endl << "Game got updated of: " << this->updateCounter << " times";
}




pair<int, int> Game::render() {
	SDL_Surface* mySurf = IMG_Load(GOLD_COIN_PNG);
	SDL_Texture* myTexture = SDL_CreateTextureFromSurface(Game::renderer, mySurf);
	SDL_FreeSurface(mySurf);
	SDL_Rect sr1, sr2, dr1, dr2;
	sr1.x = sr1.y = sr2.x = sr2.y = 0;
	sr1.h = sr1.w = sr2.h = sr2.w = SCALESIZE;
	dr1.h = dr1.w = dr2.h = dr2.w = SCALESIZE;
	dr1.x = dr1.y = 32;
	dr2.x = dr2.y = 96;

	if (false != SDL_RenderClear(renderer)) {
		return make_pair (_SDL_RenderClear, SCORE_NOT_INITIALISED);
	}

	level1Map->DrawMap();
	mainPlayer->render();


	for (int i = 0; i < GoldCoinArray.size(); i++) {
		GoldCoinArray.at(i)->render();
	}

	for (int i = 0; i < SpikedTrapArray.size(); i++) {
		SpikedTrapArray.at(i)->render();
	}
	
	Game::renderScore(mainPlayer->getCurrentScore());
	Game::renderLife(mainPlayer->getCurrentLife());
	Game::renderCurrentLevelNumber(currentLevel);

	SDL_RenderPresent(renderer);

	if (mainPlayer->getCurrentLife() <= 0)
		return make_pair(PLAYER_IS_DEAD, mainPlayer->getCurrentScore());

	if (mainPlayer->getCurrentScore() / GOLD_COIN_SCORE_INCREASE == goldCoinsPerLevel[currentLevel - 1][1])
		return make_pair(PLAYER_WON_THE_LEVEL, mainPlayer->getCurrentScore());

	return make_pair(_RENDERINGSUCCES, SCORE_NOT_INITIALISED);
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

	for(int i = 0; i < GoldCoinArray.size(); i++)
		delete GoldCoinArray.at(i);

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

/*void Game::initMenu() {
	vector<menuItem> options;
	menuItem m1 = { "Start Game", nullptr };
	menuItem m2 = { "Instructions", nullptr };
	menuItem m3 = { "Exit", nullptr};
	options.push_back(m1);
	options.push_back(m2);
	options.push_back(m3);

	gameMenu = new Menu(250, 80, make_pair(10, 10), options);
}

*/

pair<int, int> Game::returnHeroCoordinates(Component* hero) {
	return make_pair(hero->getXpos(), hero->getYpos());
}


pair<int, int> Game::generateRandomCoordinates(Component* hero) {
	int xPos, yPos;

	do {
		 xPos = rand() % 20 + 1;
		 yPos = rand() % 25 + 1;
	} while (level1Map->accesMapCoordinates(xPos, yPos) < 0
		or ( returnHeroCoordinates(hero).first == xPos and returnHeroCoordinates(hero).second == yPos));

	return make_pair(xPos, yPos);
}


void Game::coinsManager(vector <GoldCoin*>& goldCoinArr, const int heroX, const int heroY, Component& mainPlayer) {
	for (int i = 0; i < goldCoinArr.size(); i++) {
		if (goldCoinArr.at(i)->getYpos() == heroY and goldCoinArr.at(i)->getXpos() == heroX) {
			mainPlayer.increaseScore(GOLD_COIN_SCORE_INCREASE);
			delete goldCoinArr.at(i);
			goldCoinArr.erase(goldCoinArr.begin() + i);
		}
	}
}


void Game::trapsManager(vector <SpikedTrap*> & SpikedTrapArray, const int heroX, const int heroY, Component& mainPlayer) {
	for (int i = 0; i < SpikedTrapArray.size(); i++) {
		if (SpikedTrapArray.at(i)->getYpos() == heroY and SpikedTrapArray.at(i)->getXpos() == heroX) {
			mainPlayer.decreaseHealth(SPIKED_BALL_DAMAGE);
			delete SpikedTrapArray.at(i);
			SpikedTrapArray.erase(SpikedTrapArray.begin() + i);
		}
	}
}

void Game::renderScore(const int currentScore) {
	string textToDisplay = "CURRENT SCORE: " + to_string(currentScore);
	TTF_Font* tahoma = TTF_OpenFont(ARCHERY_BLACK, 20);
	SDL_Rect blittingRectangle;
	blittingRectangle.x = 620;
	blittingRectangle.y = 0;
	blittingRectangle.h = 32;
	blittingRectangle.w = 150;

	SDL_Surface * textSurface = TTF_RenderText_Blended_Wrapped(tahoma, textToDisplay.c_str(), SDL_Color({ 230,230,250 }), 350);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	SDL_FreeSurface(textSurface);
	SDL_RenderCopy(Game::renderer, textTexture, nullptr, &blittingRectangle);
}

void Game::renderLife(const int currentLife) {
	string textToDisplay = "HEALTH: " + to_string(currentLife);
	TTF_Font* tahoma = TTF_OpenFont(ARCHERY_BLACK, 20);
	SDL_Rect blittingRectangle;
	blittingRectangle.x = 30;
	blittingRectangle.y = 0;
	blittingRectangle.h = 32;
	blittingRectangle.w = 150;

	SDL_Surface * textSurface = TTF_RenderText_Blended_Wrapped(tahoma, textToDisplay.c_str(), SDL_Color({ 255,160,122 }), 350);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	SDL_FreeSurface(textSurface);
	SDL_RenderCopy(Game::renderer, textTexture, nullptr, &blittingRectangle);
}


void Game::renderCurrentLevelNumber(const int currentLevel) {
	string textToDisplay = "CURRENT LEVEL: " + to_string(currentLevel);
	TTF_Font* tahoma = TTF_OpenFont(ARCHERY_BLACK, 20);
	SDL_Rect blittingRectangle;
	blittingRectangle.x = 320;
	blittingRectangle.y = 0;
	blittingRectangle.h = 32;
	blittingRectangle.w = 150;

	SDL_Surface * textSurface = TTF_RenderText_Blended_Wrapped(tahoma, textToDisplay.c_str(), SDL_Color({ 0,255,255 }), 350);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	SDL_FreeSurface(textSurface);
	SDL_RenderCopy(Game::renderer, textTexture, nullptr, &blittingRectangle);
}