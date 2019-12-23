#include "TextureManager.h"


// function meant to create a texture from a given surface
 
SDL_Texture* textureManager::loadTexture(const char* texture){
	SDL_Surface* tempSurface = IMG_Load(texture);
	if (NULL == tempSurface) {
		return NULL;
	}
	SDL_Texture* myTexture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	const char* error = SDL_GetError();
	SDL_FreeSurface(tempSurface);
	return myTexture;
}

// simple function meant do draw something on the screen
void textureManager::Draw(SDL_Texture* givenTexture, SDL_Rect sourcePos, SDL_Rect destinationPos) {
	SDL_RenderCopy(Game::renderer, givenTexture, &sourcePos, &destinationPos);
}