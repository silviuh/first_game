#include "gameHandler.h"
#include "Menu.h"

Game *game = nullptr;
Menu *gameMenu = nullptr;

void displayInstructions();
void instructionsMenuManager();
void startGame();
void quitGame();


int main(int argc, char* args[])
{
	const int FPS = 100;
	const int frameDelay = 1000 / FPS; // how much time passes between 2 frame displays

	Uint32 frameStart = 0;
	Uint32 lastUpdate = 0;
	int frameTime;


	game = new Game();
	game->init((char*) "noTitleSet", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false); // we have choosen numbers that divide by 32 for the screen resolution

	vector<menuItem> options;
	menuItem m1 = { "< Start Game >", startGame };
	menuItem m2 = { "< Instructions >", instructionsMenuManager};
	menuItem m3 = { "< Exit Game >", quitGame};
	options.push_back(m1);
	options.push_back(m2);
	options.push_back(m3);

	gameMenu = new Menu(250, 80, make_pair(270, 210), options);

	while (gameMenu->menuIsActive() == true) {
		frameStart = SDL_GetTicks();

		gameMenu->drawMenu();
		gameMenu->handleEvents();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	if (gameMenu->returnRequestForExitingTheGame() == false) {
		while (true == game->gameIsRunning()) {

			frameStart = SDL_GetTicks();
			game->handleEvents();

			if (frameStart - lastUpdate >= 450) {
				game->update();
				lastUpdate = SDL_GetTicks();
			}

			int gameRenderSucces = game->render();
			if (_RENDERINGSUCCES != gameRenderSucces) {
				game->logErrorHandlerFile(gameRenderSucces, NULL);
			}

			// we want 60 frames/sec so we have to delay the current load with the difference between
			// how much time takes to load SDL once and the desired time for a single frame to take place
			frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime) {
				SDL_Delay(frameDelay - frameTime);
			}
		}
	}
	
	game->clean();
	return 0;
}

void startGame() {
	gameMenu->switchOffMenuLoop();
	game->switchOnGameLoop();
}

void quitGame() {
	gameMenu->switchOffMenuLoop();
	game->switchOffGameLoop();
}




void instructionsMenuManager() {
	gameMenu->switchOnInstructionMenu();
	SDL_Event event;
	int frameTime;
	const int frameDelay = 1000 / 100;

	while (gameMenu->checkIfinstructionsMenuIsActive() == true) {
		Uint32 frameStart = SDL_GetTicks();

		displayInstructions();

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN: {
				switch (event.key.keysym.sym) {
				case SDLK_RETURN:
					gameMenu->switchOffInstructionMenu();
					break;
				}
				break;
			}
							  // exiting the game
			case SDL_QUIT: {
				gameMenu->switchOffInstructionMenu();
				gameMenu->switchOffMenuLoop();
				gameMenu->gameExit();
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