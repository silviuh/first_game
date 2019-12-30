#include "gameHandler.h"

Game *game = nullptr;

int main(int argc, char* args[])
{
	const int FPS = 100;
	const int frameDelay = 1000 / FPS; // how much time passes between 2 frame displays

	Uint32 frameStart = 0;
	Uint32 lastUpdate = 0;
	int frameTime;


	game = new Game();
	game->init((char*) "noTitleSet", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false); // we have choosen numbers that divide by 32 for the screen resolution
	Game::initMenu();




	while (true == game->gameIsRunning()) {

		frameStart = SDL_GetTicks();
		game->handleEvents();

		if (frameStart - lastUpdate >= 450) {
			game->update();
			lastUpdate = SDL_GetTicks();
		}

		int gameRenderSucces = game->render();
		if (_RENDERINGSUCCES != gameRenderSucces){
			game->logErrorHandlerFile(gameRenderSucces, NULL);
		}

		// we want 60 frames/sec so we have to delay the current load with the difference between
		// how much time takes to load SDL once and the desired time for a single frame to take place
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	
	game->clean();
	return 0;
}