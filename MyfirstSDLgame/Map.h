#pragma once
#include "gameHandler.h"
#include "Utils.h"

// enum for drawable elements on the map

class Map {
private:
	SDL_Rect mapSource, mapDestination;
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;
	SDL_Texture* rock;

	bool solid[_X_MAP_BOUND][_Y_MAP_BOUND];

	int map[_X_MAP_BOUND][_Y_MAP_BOUND];



public:

	Map();
	~Map();
	void LoadMap(const int myArray[_X_MAP_BOUND][_Y_MAP_BOUND]);
	void DrawMap();
	bool Collision(const int givenX, const int givenY);
	bool overlap(const SDL_Rect& src, const SDL_Rect& dest);
	int& accesMapCoordinates(const int givenX, const int givenY) {
		return map[givenX][givenY];
	}


	int& operator()(const int givenX, const int givenY){
		return map[givenX][givenY];
	}

	static bool insideBoundaries(const int givenX, const int givenY);
		// we will think about this depending how we will move the player or the mob
};