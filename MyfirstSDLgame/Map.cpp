#pragma once
#include "Map.h"
#include "TextureManager.h"

Map::Map() {
	this->dirt = textureManager::loadTexture(SAND_PNG);
	this->grass = textureManager::loadTexture(GRASS_PNG);
	this->water = textureManager::loadTexture(SKY_PNG);
	this->rock = textureManager::loadTexture(GRAYBRICK_PNG);

	this->mapSource.w = this->mapSource.h = SCALESIZE;
	this->mapDestination.x = this->mapDestination.y = 0;
	this->mapDestination.w = this->mapDestination.h = SCALESIZE;

}

void Map::DrawMap() {
	int type = 0;
	for (int row = 0; row < _X_MAP_BOUND; row++) {
		for (int column = 0; column < _Y_MAP_BOUND; column++) {
			type = this->map[row][column];
			this->mapDestination.x = column * SCALESIZE;
			this->mapDestination.y = row * SCALESIZE;

			switch (type)
			{
			case Water:
				textureManager::Draw(this->water, this->mapSource, this->mapDestination);
				break;
			case Grass:
				textureManager::Draw(this->grass, this->mapSource, this->mapDestination);
				break;
			case Dirt:
				textureManager::Draw(this->dirt, this->mapSource, this->mapDestination);
				break;
			case Rock:
				textureManager::Draw(this->rock, this->mapSource, this->mapDestination);
				break;
			default:
				break;
			}
		}
	}
}

void Map::LoadMap(const string filePath) {
	std::fstream mapFile;
	mapFile.open(filePath);
	char tile;

	for (int i = 0; i < _X_MAP_BOUND; i++) {
		for (int j = 0; j < _Y_MAP_BOUND; j++) {
			mapFile.get(tile);
			if (tile == '-') {
				mapFile.get(tile);
				map[i][j] = -atoi(&tile);
			}
			else if( atoi(&tile) > 0)
				map[i][j] = atoi(&tile);

			mapFile.ignore();
			mapFile.ignore(); 
		}
	}
	mapFile.close();
}

bool Map::Collision(const int givenX, const int givenY) {
	return map[givenY][givenX] < 0;
}

bool Map::overlap(const SDL_Rect& src, const SDL_Rect& dest) {
	if (
		src.x + src.w >= dest.x and
		dest.x + dest.w >= src.x and
		src.y + src.h >= dest.y and
		dest.y + dest.h >= src.y
		)
		return true;
	return false;
}


bool Map::insideBoundaries(const int givenX, const int givenY) {
	return(givenX > 0 and givenX < _X_MAP_BOUND and givenY > 0 and givenY < _Y_MAP_BOUND);
}
