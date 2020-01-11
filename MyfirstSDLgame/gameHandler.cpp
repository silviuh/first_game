#pragma once
#include "gameHandler.h"
#include "Menu.h"
#include "Utils.h"
#include "Hero.h"
#include "SpecializedHeroClassVoidWalker.h"
#include "SpecializedHeroClassMage.h"
#include "SpecializedHeroKnight.h"
#include "Mob.h"
#include "UpgradedMobs.h"
#include "GoldCoin.h"
#include "SpikedTrap.h"
#include "TextureManager.h"
#include "HeartBonus.h"
#include "Map.h"


SDL_Renderer* Game::renderer = nullptr;
int Game::heroDirection = UNSET;
Map* Game::levelMap = nullptr;
int Mob::mobCounter = 0;
int Mob::movementTime = 0;
vector < pair<Level, levelSpecificDataContainer> > Game::storageContainerForLevels;



//  <----------------------------------------     GAME INITIALIZATION    ---------------------------------------->
Game ::Game() {
	this->isRunning = false;
	this->window = nullptr;
	srand(time(NULL));
	voidHoleColdown = 0;
}

Game::~Game() {

}


void Game::createHeroes() {
	delete mainPlayer;
	if (selectedCharacter == "VOID_WALKER")
		mainPlayer = new SpecializedHeroClassVoidWalker(VOID_WALKER_PNG, STARTING_X_POS, STARTING_Y_POS, MAX_HERO_HEALTH, levelMap);
	else if (selectedCharacter == "MAGE")
		mainPlayer = new SpecializedHeroClassMage(MAGE_PNG, STARTING_X_POS, STARTING_Y_POS, MAX_HERO_HEALTH, levelMap), mainPlayer->addMobsArr(MobsArray);
	else if (selectedCharacter == "KNIGHT")
		mainPlayer = new SpecializedHeroKnight(KNIGHT_PNG, STARTING_X_POS, STARTING_Y_POS, MAX_HERO_HEALTH, levelMap), mainPlayer->addMobsArr(MobsArray);

	for (int i = 0; i < MobsArray.size(); i++) {
		MobsArray.at(i)->setHeroRefference(mainPlayer);
	}
	for (int i = 0; i < heartsArray.size(); i++) {
		heartsArray.at(i)->setHeroRefference(mainPlayer);
	}
}


int Game::init(char* gameTitle, int xpos, int ypos, int width, int height, bool fullScreen, int currentLevelInGame) {
	int flags = false;
	fullScreen ? flags = SDL_WINDOW_FULLSCREEN : flags = false;

	if (false == SDL_Init(SDL_INIT_EVERYTHING)) {
		this->window = SDL_CreateWindow(gameTitle, xpos, ypos, width, height, flags);

		if (false == window)
			LOG_ERROR("SDL_CreateWindow failed", 63);


		SDL_Renderer* asd = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		LOG_ERROR("SDL_CreateRenderer failed", 67);
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
		LOG_ERROR("SDL_Init failed", 81);

	Game::initializeStorageContainerForLevels(Game::storageContainerForLevels);

	currentLevel = currentLevelInGame;
	levelMap = new Map();
	mainPlayer = new Hero(HERO_PNG, STARTING_X_POS, STARTING_Y_POS, 100);

	if (selectedCharacter == "VOID_WALKER")
		mainPlayer = new Hero(VOID_WALKER_PNG, STARTING_X_POS, STARTING_Y_POS, MAX_HERO_HEALTH);
	else if (selectedCharacter == "MAGE")
		mainPlayer = new Hero(MAGE_PNG, STARTING_X_POS, STARTING_Y_POS, MAX_HERO_HEALTH);
	else if (selectedCharacter == "KNIGHT")
		mainPlayer = new Hero(KNIGHT_PNG, STARTING_X_POS, STARTING_Y_POS, MAX_HERO_HEALTH);

	levelMap->LoadMap(Game::storageContainerForLevels.at(currentLevel - 1).second.mapFilePath);
	generateBluePrintMap();


	vector <pair<int, int>> coinList;
	generateRandomCoordinates(coinList, mainPlayer,
							 Game::storageContainerForLevels.at(currentLevel - 1).second.numberOfCoins,
							 mapBluePrint, levelMap);

	for (int i = 0; i < Game::storageContainerForLevels.at(currentLevel - 1).second.numberOfCoins; i++) {
		pair<int, int> tempPair = coinList.at(i);
		GoldCoin* newGoldCoin = new GoldCoin(GOLD_COIN_PNG, tempPair.first, tempPair.second);
		GoldCoinArray.push_back(newGoldCoin);
		mapBluePrint[tempPair.first][tempPair.second] = COIN_ON_MAP;
	}



	vector <pair<int, int>> heartList;
	generateRandomCoordinates(heartList, mainPlayer,
		Game::storageContainerForLevels.at(currentLevel - 1).second.numberOfHeartsPerLevel,
		mapBluePrint, levelMap);

	for (int i = 0; i < Game::storageContainerForLevels.at(currentLevel - 1).second.numberOfHeartsPerLevel; i++) {
		pair<int, int> tempPair = heartList.at(i);
		HeartBonus* newHeartBonus = new HeartBonus(LIFE_BONUS_PNG, tempPair.first, tempPair.second, 0, LIFE_BONUS, mainPlayer);
		heartsArray.push_back(newHeartBonus);
		mapBluePrint[tempPair.first][tempPair.second] = HEART_ON_MAP;
	}



	vector <pair <int, int>> spikeyBallList;
	generateRandomCoordinates(spikeyBallList, mainPlayer,
		Game::storageContainerForLevels.at(currentLevel - 1).second.numberOfSpikedBalls,
		mapBluePrint, levelMap);

	for (int i = 0; i < Game::storageContainerForLevels.at(currentLevel - 1).second.numberOfSpikedBalls; i++) {
		pair<int, int> tempPair = spikeyBallList.at(i);
		SpikedTrap* newSpikeyBall = new SpikedTrap(SPIKEY_BALL_PNG, tempPair.first, tempPair.second);
		SpikedTrapArray.push_back(newSpikeyBall);
		mapBluePrint[tempPair.first][tempPair.second] = SPIKY_BALL_ON_MAP;
	}




	vector <pair <int, int>> basicMobList;
	generateRandomCoordinates(basicMobList, mainPlayer,
							 Game::storageContainerForLevels.at(currentLevel - 1).second.numberOfBasicMobs,
							 mapBluePrint, levelMap);

	for (int i = 0; i < Game::storageContainerForLevels.at(currentLevel - 1).second.numberOfBasicMobs; i++) {
		pair<int, int> tempPair = basicMobList.at(i);
		Component* newBasicMob = new  Mob(MOB_LVL_1, tempPair.first, tempPair.second, BASIC_MOB_HEALTH, mainPlayer, BASIC_MOB_DAMAGE);
		MobsArray.push_back(newBasicMob);
		mapBluePrint[tempPair.first][tempPair.second] = BASIC_MOB_ON_MAP;
	}




	vector <pair <int, int>> upgradedMobList;
	generateRandomCoordinates(upgradedMobList, mainPlayer,
							  Game::storageContainerForLevels.at(currentLevel - 1).second.numberOfUpgradedMobs,
						      mapBluePrint, levelMap);

	for (int i = 0; i < Game::storageContainerForLevels.at(currentLevel - 1).second.numberOfUpgradedMobs; i++) {
		pair<int, int> tempPair = upgradedMobList.at(i);
		Component* newUpgradedMob = new UpgradedMobs(MOB_LVL_2, tempPair.first, tempPair.first, UPGRADED_MOB_HEALTH, mainPlayer, UPGRADED_MOB_DAMAGE);
		MobsArray.push_back(newUpgradedMob);
		mapBluePrint[tempPair.first][tempPair.second] = UPGRADED_MOB_ON_MAP;
	}
}



void Game::initializeStorageContainerForLevels(vector < pair<Level, levelSpecificDataContainer> > & givenVector) {
	levelSpecificDataContainer genericLevel;

	genericLevel.mapFilePath = FILE_PATH_MAP_LEVEL_1;
	genericLevel.numberOfBasicMobs = NUMBER_OF_MOBS_LEVEL_1;
	genericLevel.numberOfCoins = NUMBER_OF_GOLD_COINS_LEVEL1;
	genericLevel.numberOfMobs = NUMBER_OF_MOBS_LEVEL_1;
	genericLevel.numberOfSpikedBalls = NUMBER_OF_SPIKED_BALLS_LEVEL_1;
	genericLevel.numberOfUpgradedMobs = NUMBER_OF_UPGRADED_MOBS_LEVEL_1;
	genericLevel.numberOfHeartsPerLevel = NUMBER_OF_HEARTS_LEVEL_1;
	givenVector.push_back(make_pair(LEVEL_1, genericLevel));

	genericLevel.mapFilePath = FILE_PATH_MAP_LEVEL_2;
	genericLevel.numberOfBasicMobs = NUMBER_OF_BASIC_MOBS_LEVEL_2;
	genericLevel.numberOfCoins = NUMBER_OF_GOLD_COINS_LEVEL2;
	genericLevel.numberOfMobs = NUMBER_OF_MOBS_LEVEL_2;
	genericLevel.numberOfSpikedBalls = NUMBER_OF_SPIKED_BALLS_LEVEL_2;
	genericLevel.numberOfUpgradedMobs = NUMBER_OF_UPGRADED_MOBS_LEVEL_2;
	genericLevel.numberOfHeartsPerLevel = NUMBER_OF_HEARTS_LEVEL_2;
	givenVector.push_back(make_pair(LEVEL_2, genericLevel));

	genericLevel.numberOfHeartsPerLevel = NUMBER_OF_HEARTS_LEVEL_1;
	genericLevel.mapFilePath = FILE_PATH_MAP_LEVEL_3;
	genericLevel.numberOfBasicMobs = NUMBER_OF_BASIC_MOBS_LEVEL_3;
	genericLevel.numberOfCoins = NUMBER_OF_GOLD_COINS_LEVEL3;
	genericLevel.numberOfMobs = NUMBER_OF_MOBS_LEVEL_3;
	genericLevel.numberOfSpikedBalls = NUMBER_OF_SPIKED_BALLS_LEVEL_3;
	genericLevel.numberOfUpgradedMobs = NUMBER_OF_UPGRADED_MOBS_LEVEL_3;
	genericLevel.numberOfHeartsPerLevel = NUMBER_OF_HEARTS_LEVEL_3;
	givenVector.push_back(make_pair(LEVEL_3, genericLevel));
}
//  <----------------------------------------      END     ---------------------------------------->










//  <----------------------------------------     GAME HANDLING AND UPDATE  ---------------------------------------->
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
			case SDLK_SPACE:
				mainPlayer->toogleOnAbility();
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
	
	Game::trapsManager(SpikedTrapArray, MobsArray,  mainPlayer->getXpos(), mainPlayer->getYpos(), *mainPlayer);
	Game::mobsManager(MobsArray, mainPlayer->getXpos(), mainPlayer->getYpos(), *mainPlayer, SpikedTrapArray);
	Game::coinsManager(GoldCoinArray, mainPlayer->getXpos(), mainPlayer->getYpos(), *mainPlayer);
	Game::heartBonuses(heartsArray, mainPlayer->getXpos(), mainPlayer->getYpos());

	Mob::movementTime++;

	if (Mob::movementTime % BASIC_MOBS_MOVEMENT_PERIOD == 0) {
		for (int i = 0; i < Game::storageContainerForLevels.at(currentLevel - 1).second.numberOfBasicMobs; i++) {
			MobsArray.at(i)->update();
		}
	}

	if (Mob::movementTime % UPGRADED_MOBS_MOVEMENT_PERIOD == 0) {
		for (int i = Game::storageContainerForLevels.at(currentLevel - 1).second.numberOfBasicMobs; i < MobsArray.size(); i++) {
			MobsArray.at(i)->update();
		}
	}


	if (mainPlayer->getAbilityColdown() > 0) {
		mainPlayer->reduceAbilityColdown();
	}

	if (mainPlayer->getAbilityColdown() == 0)
		mainPlayer->toogleAbilityCanBeCastedFlag();
}

pair<int, int> Game::returnHeroCoordinates(Component* hero) {
	return make_pair(hero->getXpos(), hero->getYpos());
}
;

void Game::generateBluePrintMap() {
	for (int i = 0; i < _X_MAP_BOUND; i++)
		for (int j = 0; j < _Y_MAP_BOUND; j++)
			mapBluePrint[i][j] = levelMap->accesMapCoordinates(i, j);
}

bool Game::notInBluePrintMap(int mapBluePrint[_X_MAP_BOUND][_Y_MAP_BOUND], int xPos, int yPos) {
	return (mapBluePrint[xPos][yPos] < 0);
}

void Game::generateRandomCoordinates(vector <pair<int, int>> & list, Component* hero, int sizeOfRequieredList, int mapBluePrint[_X_MAP_BOUND][_Y_MAP_BOUND], Map* levelMap) {
	int heroX = hero->getXpos();
	int heroY = hero->getYpos();
	int xPos, yPos;
	bool inVector;

	for (int i = 0; i < sizeOfRequieredList; i++) {
		do {
			inVector = false;
			xPos = rand() % (_X_MAP_BOUND - 3) + 2;
			yPos = rand() % (_Y_MAP_BOUND - 3) + 2;
			for (int i = 0; i < list.size(); i++)
				if (make_pair(xPos, yPos) == list.at(i))
					inVector = true;

		} while (Game::notInBluePrintMap(mapBluePrint, xPos, yPos)
			or inVector or levelMap->accesMapCoordinates(yPos, xPos) < 0);
		list.push_back(make_pair(xPos, yPos));
	}
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


void Game::trapsManager(vector <SpikedTrap*> & SpikedTrapArray, vector <Component*> & mobsArray, const int heroX, const int heroY, Component& mainPlayer) {
	for (int i = 0; i < SpikedTrapArray.size(); i++) {
		if (SpikedTrapArray.at(i)->isComponentActive()) {
			if (SpikedTrapArray.at(i)->getYpos() == heroY and SpikedTrapArray.at(i)->getXpos() == heroX) {
				mainPlayer.decreaseHealth(SPIKED_BALL_DAMAGE);
				SpikedTrapArray.at(i)->makeComponentInactive();
			}
		}

		for (int i = 0; i < SpikedTrapArray.size(); i++)
			if (SpikedTrapArray.at(i)->isComponentActive()) {
				for (int j = 0; j < mobsArray.size(); j++) {
					if (mobsArray.at(j)->isComponentActive()) {
						if (SpikedTrapArray.at(i)->getXpos() == mobsArray.at(j)->getXpos() and SpikedTrapArray.at(i)->getYpos() == mobsArray.at(j)->getYpos()) {
							mobsArray.at(j)->decreaseHealth(SPIKED_BALL_DAMAGE);
							SpikedTrapArray.at(i)->makeComponentInactive();
							if (mobsArray.at(j)->getCurrentLife() <= 0)
								mobsArray.at(j)->makeComponentInactive();
						}
					}
				}
			}
	}
}


void Game::mobsManager(vector <Component*> & mobsArray, const int heroX, const int heroY, Component& mainPlayer, vector <SpikedTrap*> & SpikedTrapArray) {
	for (int i = 0; i < mobsArray.size(); i++) {
		if (mobsArray.at(i)->isComponentActive() and mobsArray.at(i)->playerIsInVision(10))
			if (mobsArray.at(i)->getYpos() == heroY and mobsArray.at(i)->getXpos() == heroX) {
				mainPlayer.decreaseHealth(BASIC_MOB_DAMAGE);
			}
		if (mobsArray.at(i)->getCurrentLife() <= 0)
			mobsArray.at(i)->makeComponentInactive();
	}
}


void Game::heartBonuses(vector <HeartBonus*> & heartArr, const int heroX, const int heroY) {
	for (int i = 0; i < heartArr.size(); i++) {
		if (heartArr.at(i)->isComponentActive())
			if (heartArr.at(i)->getYpos() == heroY and heartArr.at(i)->getXpos() == heroX) {
				heartArr.at(i)->HeroGetsBonus();
				heartArr.at(i)->makeComponentInactive();
			}
	}
}
//  <----------------------------------------    END   ---------------------------------------->










//  <----------------------------------------     GAME RENDER    ---------------------------------------->
pair<int, int> Game::render() {
	SDL_Surface* mySurf = IMG_Load(GOLD_COIN_PNG);
	if (nullptr == mySurf)
		LOG_ERROR("IMG_Load failed", 277);

	SDL_Texture* myTexture = SDL_CreateTextureFromSurface(Game::renderer, mySurf);
	if(nullptr == myTexture)
		LOG_ERROR("IMG_Load failed", 281);

	SDL_FreeSurface(mySurf);
	SDL_Rect sr1, sr2, dr1, dr2;
	sr1.x = sr1.y = sr2.x = sr2.y = 0;
	sr1.h = sr1.w = sr2.h = sr2.w = SCALESIZE;
	dr1.h = dr1.w = dr2.h = dr2.w = SCALESIZE;
	dr1.x = dr1.y = 32;
	dr2.x = dr2.y = 96;

	if (false != SDL_RenderClear(renderer)) {
		LOG_ERROR("SDL_RenderClear failed", 292);
	}

	levelMap->DrawMap();
	mainPlayer->render();

	for (int i = 0; i < SpikedTrapArray.size(); i++) {
		if (SpikedTrapArray.at(i)->isComponentActive())
			SpikedTrapArray.at(i)->render();
	}

	for (int i = 0; i < MobsArray.size(); i++) {
		if (MobsArray.at(i)->isComponentActive())
			MobsArray.at(i)->render();
	}

	for (int i = 0; i < GoldCoinArray.size(); i++) {
		GoldCoinArray.at(i)->render();
	}

	for (int i = 0; i < heartsArray.size(); i++) {
		if (heartsArray.at(i)->isComponentActive())
			heartsArray.at(i)->render();
	}

	Game::renderScore(mainPlayer->getCurrentScore());
	Game::renderLife(mainPlayer->getCurrentLife());
	Game::renderCurrentLevelNumber(currentLevel);

	SDL_RenderPresent(renderer);

	if (mainPlayer->getCurrentLife() <= 0)
		return make_pair(PLAYER_IS_DEAD, mainPlayer->getCurrentScore());

	if (GoldCoinArray.size() == NO_COINS_LEFT)
		return make_pair(PLAYER_WON_THE_LEVEL, mainPlayer->getCurrentScore());

	return make_pair(_RENDERINGSUCCES, SCORE_NOT_INITIALISED);
} 

void Game::renderScore(const int currentScore) {
	string textToDisplay = "CURRENT SCORE: " + to_string(currentScore);
	TTF_Font* tahoma = TTF_OpenFont(ARCHERY_BLACK, 20);
	if (nullptr == tahoma)
		LOG_ERROR("TTF_OpenFont failed", 494);

	SDL_Rect blittingRectangle;
	blittingRectangle.x = 620;
	blittingRectangle.y = 0;
	blittingRectangle.h = 32;
	blittingRectangle.w = 150;

	SDL_Surface * textSurface = TTF_RenderText_Blended_Wrapped(tahoma, textToDisplay.c_str(), SDL_Color({ 230,230,250 }), 350);
	if (nullptr == textSurface)
		LOG_ERROR("TTF_RenderText_Blended_Wrapped failed", 504);

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	if (nullptr == textTexture)
		LOG_ERROR("SDL_CreateTextureFromSurface failed", 508);

	SDL_FreeSurface(textSurface);
	SDL_RenderCopy(Game::renderer, textTexture, nullptr, &blittingRectangle);
}

void Game::renderLife(const int currentLife) {
	string textToDisplay = "HEALTH: " + to_string(currentLife);
	TTF_Font* tahoma = TTF_OpenFont(ARCHERY_BLACK, 20);
	if (nullptr == tahoma)
		LOG_ERROR("TTF_OpenFont failed", 516);

	SDL_Rect blittingRectangle;
	blittingRectangle.x = 30;
	blittingRectangle.y = 0;
	blittingRectangle.h = 32;
	blittingRectangle.w = 150;

	SDL_Surface * textSurface = TTF_RenderText_Blended_Wrapped(tahoma, textToDisplay.c_str(), SDL_Color({ 255,160,122 }), 350);
	if (nullptr == textSurface)
		LOG_ERROR("TTF_RenderText_Blended_Wrapped failed", 526);

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	if (nullptr == textTexture)
		LOG_ERROR("SDL_CreateTextureFromSurface failed", 530);

	SDL_FreeSurface(textSurface);
	SDL_RenderCopy(Game::renderer, textTexture, nullptr, &blittingRectangle);
}


void Game::renderCurrentLevelNumber(const int currentLevel) {
	string textToDisplay = "CURRENT LEVEL: " + to_string(currentLevel);
	TTF_Font* tahoma = TTF_OpenFont(ARCHERY_BLACK, 20);
	if (nullptr == tahoma)
		LOG_ERROR("TTF_OpenFont failed", 541);

	SDL_Rect blittingRectangle;
	blittingRectangle.x = 320;
	blittingRectangle.y = 0;
	blittingRectangle.h = 32;
	blittingRectangle.w = 150;

	SDL_Surface * textSurface = TTF_RenderText_Blended_Wrapped(tahoma, textToDisplay.c_str(), SDL_Color({ 0,255,255 }), 350);
	if (nullptr == textSurface)
		LOG_ERROR("TTF_RenderText_Blended_Wrapped failed", 551);

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	if (nullptr == textTexture)
		LOG_ERROR("SDL_CreateTextureFromSurface failed", 555);

	SDL_FreeSurface(textSurface);
	SDL_RenderCopy(Game::renderer, textTexture, nullptr, &blittingRectangle);
}


void Game::renderVoidHole(Component* hero) {
	TTF_Font* tahoma = TTF_OpenFont(ARCHERY_BLACK, 20);
	if (nullptr == tahoma)
		LOG_ERROR("TTF_OpenFont failed", 565);

	SDL_Rect blittingRectangle;
	blittingRectangle.x = hero->getXpos();
	blittingRectangle.y = hero->getYpos();
	blittingRectangle.h = SCALESIZE;
	blittingRectangle.w = SCALESIZE;

	SDL_Texture* voidHoleTexture = textureManager::loadTexture(VOID_HOLE_PNG);
	SDL_RenderCopy(Game::renderer, voidHoleTexture, nullptr, &blittingRectangle);
}

//  <----------------------------------------    END    ---------------------------------------->










//  <----------------------------------------    GAME CLEAN_UP    ---------------------------------------->
int Game::clean() {
	this->isRunning = false;

	if(nullptr != this->window)
		SDL_DestroyWindow(this->window);

	if (nullptr != renderer)
		SDL_DestroyRenderer(renderer);

	for(int i = 0; i < GoldCoinArray.size(); i++)
		delete GoldCoinArray.at(i);
	for (int i = 0; i < SpikedTrapArray.size(); i++)
		delete SpikedTrapArray.at(i);
	for (int i = 0; i < MobsArray.size(); i++)
		delete MobsArray.at(i);
	for (int i = 0; i < heartsArray.size(); i++)
		delete heartsArray.at(i);

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
//  <----------------------------------------    END    ---------------------------------------->



