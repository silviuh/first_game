#include "gameHandler.h"
#include "LevelManager.h"
#include "EndGameMenu.h"
#include "CharacterMenu.h"

bool restartGameFlag = false;
bool backToMainMenuFlag = false;
int totalScore = 0;

Game *game = nullptr;
Menu *endGameMenu = nullptr;
Menu* mainMenu = nullptr;
Menu* characterMenu;
LevelManager *gameLevelManager = nullptr;

Menu* endGameMenuInit(int finalScore, int levelReached);
Menu* mainMenuInit();

void displayInstructions();
void instructionsMenuManager();
void startGame();
void mainMenuQuitGame();

void restartGame();
void backToMyMenu();
void endMenuQuitGame();


int main(int argc, char* args[])
{
	const int FPS = 100;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart = 0;
	Uint32 lastUpdate = 0;
	int frameTime;

	game = new Game();
	game->init((char*) "IN DIRE NEED FOR SOME COIN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false, LEVEL_1);
	gameLevelManager = new LevelManager(game);
	mainMenu = mainMenuInit();

	
	MainMenuLabel:
	while (mainMenu->menuIsActive() == true) {
		frameStart = SDL_GetTicks();

		mainMenu->drawMenu();
		mainMenu->handleEvents();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}


	if (mainMenu->returnRequestForExitingTheGame() == false) {
		characterMenu = new CharacterMenu(250, 80, make_pair(270, 210), vector<menuItem>());
		characterMenu->characterDataInit();

		while (characterMenu->menuIsActive() == true) {
			frameStart = SDL_GetTicks();

			characterMenu->drawMenu();
			characterMenu->handleEvents();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime) {
				SDL_Delay(frameDelay - frameTime);
			}
		}

		gameLevelManager->setCurrentCharacterInGame(characterMenu->getSelectedCharacter());
		game->setCharacter(characterMenu->getSelectedCharacter());
		game->createHeroes();

		if (characterMenu->returnRequestForExitingTheGame() == false) {
		GamePlayLabel:
			while (true == game->gameIsRunning()) {

				frameStart = SDL_GetTicks();
				game->handleEvents();

				if (frameStart - lastUpdate >= 300) {
					game->update();
					lastUpdate = SDL_GetTicks();
				}

				pair<int, int> playerStatus = game->render();
				if (playerStatus.first == PLAYER_IS_DEAD) {
					totalScore += playerStatus.second;
					Menu* endGameMenu = endGameMenuInit(totalScore, game->currentLevel);
					endGameMenu->showMessageWhenPlayerDies = true;

					while (endGameMenu->menuIsActive() == true) {
						frameStart = SDL_GetTicks();

						endGameMenu->drawMenu();
						endGameMenu->handleEvents();

						switch (endGameMenu->optionsFlag) {
						case RESTART_GAME_FLAG:
							goto GamePlayLabel;
							break;
						case BACK_TO_MY_MENU_FLAG:
							goto MainMenuLabel;
							break;
						case QUIT_GAME_FLAG:
							cout << "\n You exited the game!";
							break;
						default:
							break;
						}

						frameTime = SDL_GetTicks() - frameStart;

						if (frameDelay > frameTime) {
							SDL_Delay(frameDelay - frameTime);
						}
					}
				}

				else if (playerStatus.first == PLAYER_WON_THE_LEVEL) {
					gameLevelManager->getCurrentScoreOnLevelSucces(playerStatus.second);
					totalScore += playerStatus.second;
					game = gameLevelManager->loadNextLevel();

				}
			}
		}
	}
	
	delete mainMenu;
	delete endGameMenu;
	delete characterMenu;
	game->clean();
	return 0;
}

void startGame() {
	mainMenu->switchOffMenuLoop();
	game->switchOnGameLoop();
}

void mainMenuQuitGame() {
	mainMenu->switchOffMenuLoop();
	mainMenu->gameExit();
	game->switchOffGameLoop();
}

void instructionsMenuManager() {
	mainMenu->switchOnInstructionMenu();
	SDL_Event event;
	int frameTime;
	const int frameDelay = 1000 / 100;

	while (mainMenu->checkIfinstructionsMenuIsActive() == true) {
		Uint32 frameStart = SDL_GetTicks();

		displayInstructions();

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN: {
				switch (event.key.keysym.sym) {
				case SDLK_RETURN:
					mainMenu->switchOffInstructionMenu();
					break;
				}
				break;
			}

			case SDL_QUIT: {
				mainMenu->switchOffInstructionMenu();
				mainMenu->switchOffMenuLoop();
				mainMenu->gameExit();
				break;
			}
			}
		}

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
}


void displayInstructions() {
	SDL_RenderClear(Game::renderer);
	TTF_Font *font = TTF_OpenFont(TAHOMA, 20);

	SDL_Rect blittingRectangle;
	blittingRectangle.x = 170;
	blittingRectangle.y = 160;
	blittingRectangle.h = 350;
	blittingRectangle.w = 450;

	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, INSTRUCTIONS_TEXT, SDL_Color({ 255, 0, 0 }), 350);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	SDL_RenderCopy(Game::renderer, textTexture, nullptr, &blittingRectangle);

	SDL_RenderPresent(Game::renderer);
	SDL_FreeSurface(textSurface);
}

Menu* endGameMenuInit(int finalScore, int levelReached) {
	vector<menuItem> optionsForEndGameMenu;
	menuItem m1 = { "< Restart Game? >", restartGame };
	menuItem m2 = { "< Back to Main Menu >", backToMyMenu };
	menuItem m3 = { "< Exit Game >", endMenuQuitGame };
	optionsForEndGameMenu.push_back(m1);
	optionsForEndGameMenu.push_back(m2);
	optionsForEndGameMenu.push_back(m3);

	endGameMenu = new EndGameMenu(250, 80, make_pair(270, 400), optionsForEndGameMenu, finalScore, levelReached);
	return endGameMenu;
}

Menu* mainMenuInit(){
	vector<menuItem> optionsForMainMenu;
	menuItem m1 = { "< Start Game >", startGame };
	menuItem m2 = { "< Instructions >", instructionsMenuManager };
	menuItem m3 = { "< Exit Game >", mainMenuQuitGame };
	optionsForMainMenu.push_back(m1);
	optionsForMainMenu.push_back(m2);
	optionsForMainMenu.push_back(m3);

	mainMenu = new Menu(250, 80, make_pair(270, 210), optionsForMainMenu);
	return mainMenu;
}

void restartGame() {
	endGameMenu->switchOffMenuLoop();

	game->clean();
	delete game;
	game = new Game();
	game->init((char*) "IN DIRE NEED FOR SOME COIN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false, LEVEL_1);
	game->setCharacter(gameLevelManager->getCurrentCharacterInGame());
	game->createHeroes();

	endGameMenu->optionsFlag = RESTART_GAME_FLAG;
}

void backToMyMenu() {
	restartGame();

	mainMenu->switchOnMenuLoop();
	characterMenu->switchOnMenuLoop();
	mainMenu->switchOnInstructionMenu();
	endGameMenu->optionsFlag = BACK_TO_MY_MENU_FLAG;
}

void endMenuQuitGame() {
	endGameMenu->switchOffMenuLoop();
	mainMenu->switchOffMenuLoop();
	characterMenu->switchOffMenuLoop();
	game->switchOffGameLoop();

	endGameMenu->optionsFlag = QUIT_GAME_FLAG;
}