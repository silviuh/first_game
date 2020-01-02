#pragma once
#include <SDL.h>




#define ERROR_BASE_CODE 10305670

#define _INITSUCCES 77777770
#define _RENDERINGSUCCES 77777771
#define _CLEANUPSUCCES 77777772



// <---------------------------------------- DEFINES FOR GTAPIHCS USAGE ---------------------------------------->
#define UNDEFINED_SCORE -1
#define _X_MAP_BOUND 20
#define _Y_MAP_BOUND 25
#define SCALESIZE 32
#define GOLD_COINS_LEVEL1 10
#define GOLD_COIN_SCORE_INCREASE 10
#define SPIKED_BALL_DAMAGE 50
#define NUMBER_OF_SPIKED_BALLS_LEVEL_1 3

#define GRASS_PNG "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\grassTile.png"
#define SAND_PNG "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\sand.png"
#define SKY_PNG "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\sky.png"
#define GRAYBRICK_PNG "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\graybrick.png"
#define SPIKEY_BALL_PNG "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\spiky_ball.png"
#define FONT_MENU_ASSET "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\menuFont.otf"
#define GOLD_COIN_PNG "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\goldCoin.png"

#define EYE_BOT "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\eyebot.png"
#define HERO_PNG "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\king2.png"

#define MOB_LVL_1 "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\eyebot.png"
#define MOB_LVL_2 "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\eyelander.png"

#define ARCHERY_BLACK "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\archeryBlack.ttf"
#define TAHOMA "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\TAHOMA.ttf"
#define BALOO "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\baloo.ttf"
//  <----------------------------------------      END DEFINES     ---------------------------------------->




enum ErrorFlagSystem {
	_windowFullScreen = ERROR_BASE_CODE,
	_windowInitEverything,
	_sdlCreateWindow,
	_sdlCreateRenderer,
	_SDL_RenderClear,
	_SDL_DestroyWindow,
	_SDL_DestroyRenderer,
	_SDL_SetRenderDrawColor,
	_SDL_IMG_Load,
	_SDL_CreateTextureFromSurface,
	_SDL_RenderCopy
};

enum Direction {
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3,
	UNSET = -1
};

enum {
	Water,
	Grass,
	Dirt,
	Rock = -1
};

#define VISITED 999

const int dirX[] = { 0, 1, 0, -1 };
const int dirY[] = { -1, 0, 1, 0 };


const static int lv1[_X_MAP_BOUND][_Y_MAP_BOUND] = {
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	{-1, 0, 0, 2, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	{-1, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	{-1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	{-1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	{-1, 0, 0, 0, 0, 0, 0, 1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	{-1, 0, 0, 0, 0, 0, 0, 1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	{-1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1},
	{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	{-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};


#define LOOPMENU true


#define INSTRUCTIONS_TEXT "Move the hero with w, a, s, d.  Attack the mobs with space and try to collect as many gold coins as possible with a view of increasing your high score. Have fun:) (Press enter to go back to the main menu)"