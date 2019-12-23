#pragma once
#include "gameHandler.h"

// used to load any necessary textures
class textureManager {
public:
	static SDL_Texture* loadTexture(const char* fileName);
	static void Draw(SDL_Texture* givenTexture, SDL_Rect sourcePos, SDL_Rect destinationPos);
};
