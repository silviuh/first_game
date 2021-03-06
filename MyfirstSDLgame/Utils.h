#pragma once
#include <SDL.h>




#define ERROR_BASE_CODE 10305670

#define _INITSUCCES 77777770
#define _RENDERINGSUCCES 77777771
#define _CLEANUPSUCCES 77777772



// <---------------------------------------- DEFINES FOR GAME MECHANICS AND GRAPHICS ---------------------------------------->
#define UNDEFINED_SCORE -1
#define _X_MAP_BOUND 25
#define _Y_MAP_BOUND 25
#define SCALESIZE 32
#define GOLD_COIN_SCORE_INCREASE 10
#define SPIKED_BALL_DAMAGE 50
#define BASIC_MOB_DAMAGE 10
#define UPGRADED_MOB_DAMAGE 20
#define EARTH_SMASH_DAMAGE 30

#define COIN_ON_MAP -10
#define SPIKY_BALL_ON_MAP -11
#define BASIC_MOB_ON_MAP -12
#define UPGRADED_MOB_ON_MAP -13
#define HEART_ON_MAP - 14

#define LIFE_BONUS 50

#define NUMBER_OF_SPIKED_BALLS_LEVEL_1 12
#define NUMBER_OF_SPIKED_BALLS_LEVEL_2 13
#define NUMBER_OF_SPIKED_BALLS_LEVEL_3 14

#define UNDEFINED_LIFE -1;
#define PLAYER_IS_DEAD 99
#define SCORE_NOT_INITIALISED -99
#define SCORE_GOLD_PER_COIN 10

#define BASIC_MOB_HEALTH 50
#define UPGRADED_MOB_HEALTH 60

#define NUMBER_OF_MOBS_LEVEL_1 10
#define NUMBER_OF_MOBS_LEVEL_2 10
#define NUMBER_OF_MOBS_LEVEL_3 14

#define NUMBER_OF_BASIC_MOBS_LEVEL_1 10
#define NUMBER_OF_BASIC_MOBS_LEVEL_2 4
#define NUMBER_OF_BASIC_MOBS_LEVEL_3 0

#define NUMBER_OF_UPGRADED_MOBS_LEVEL_1 0
#define NUMBER_OF_UPGRADED_MOBS_LEVEL_2 6
#define NUMBER_OF_UPGRADED_MOBS_LEVEL_3 14

#define BASIC_MOBS_VISION 6
#define UPGRADED_MOBS_VISION 9

#define ZERO_UPGRADED_MOBS 0
#define ZERO_BASIC_MOBS 0

#define BASIC_MOBS_MOVEMENT_PERIOD 3
#define UPGRADED_MOBS_MOVEMENT_PERIOD 2
#define NO_COINS_LEFT 0

#define LEVEL_1 1
#define LEVEL_2 2
#define LEVEL_3 3

#define NUMBER_OF_GOLD_COINS_LEVEL1 4
#define NUMBER_OF_GOLD_COINS_LEVEL2 6
#define NUMBER_OF_GOLD_COINS_LEVEL3 8

#define NUMBER_OF_HEARTS_LEVEL_1 1
#define NUMBER_OF_HEARTS_LEVEL_2 2
#define NUMBER_OF_HEARTS_LEVEL_3 3

#define MAX_HERO_HEALTH 100

#define STARTING_X_POS 2
#define STARTING_Y_POS 2

#define VOID_HOLE_COLDOWN 10
#define EARTH_SMASH_COLDOWN 10
#define INSTANT_KILL_COLDOWN 15

enum GOLD_COINS_LEVEL {
	GOLD_COINS_LEVEL1 = 1,
	GOLD_COINS_LEVEL2,
	GOLD_COINS_LEVEL3
};

const int goldCoinsPerLevel[3][2] = {
	{LEVEL_1, NUMBER_OF_GOLD_COINS_LEVEL1},
	{LEVEL_2, NUMBER_OF_GOLD_COINS_LEVEL2},
	{LEVEL_3, NUMBER_OF_GOLD_COINS_LEVEL3},
};

#define UNSET_FLAG -1
#define RESTART_GAME_FLAG 1
#define BACK_TO_MY_MENU_FLAG 2
#define QUIT_GAME_FLAG 3

#define PLAYER_WON_THE_LEVEL 9999

#define MAX_VALUE 999999999999
//  <----------------------------------------      END DEFINES     ---------------------------------------->








//  <----------------------------------------      DEFINES FOR FILE PATHS     ---------------------------------------->




// NOTICE : ABSOLUTE PATHS
/*
#define GRASS_PNG "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\grassTile.png"
#define SAND_PNG "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\sand.png"
#define SKY_PNG "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\sky.png"
#define SKY_PNG "Assets\\sky.png"
#define GRAYBRICK_PNG "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\graybrick.png"
#define SPIKEY_BALL_PNG "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\spiky_ball.png"
#define FONT_MENU_ASSET "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\menuFont.otf"
#define GOLD_COIN_PNG "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\goldCoin.png"

#define EYE_BOT "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\eyebot.png"
#define HERO_PNG "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\king2.png"
#define VOID_WALKER_PNG "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\voidWalker.png"
#define MAGE_PNG "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\mageClass.png"
#define KNIGHT_PNG "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\knight.png"
#define VOID_WALKER_PNG_SELECTED "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\voidWalker_selected.png"
#define KNIGHT_PNG_SELECTED "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\knight_selected.png"
#define MAGE_PNG_SELECTED "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\mage_selected.png"

#define MOB_LVL_1 "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\eyebot.png"
#define MOB_LVL_2 "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\eyelander.png"

#define LIFE_BONUS_PNG "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\lifeBonus.png"
#define VOID_HOLE_PNG "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\blackHole.png"


#define ARCHERY_BLACK "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\archeryBlack.ttf"
#define TAHOMA "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\TAHOMA.ttf"
#define BALOO "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\baloo.ttf"

#define FILE_PATH_MAP_LEVEL_1 "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\LEVEL1_MAP.txt"
#define FILE_PATH_MAP_LEVEL_2 "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\LEVEL2_MAP.txt"
#define FILE_PATH_MAP_LEVEL_3 "C:\\Users\\silviu\\source\\repos\\MyfirstSDLgame\\MyfirstSDLgame\\Assets\\LEVEL3_MAP.txt"
*/



// NOTICE : RELATIVE PATHS
#define GRASS_PNG "Assets\\grassTile.png"
#define SAND_PNG "Assets\\sand.png"
#define SKY_PNG "Assets\\sky.png"
#define GRAYBRICK_PNG "Assets\\graybrick.png"
#define SPIKEY_BALL_PNG "Assets\\spiky_ball.png"
#define FONT_MENU_ASSET "Assets\\menuFont.otf"
#define GOLD_COIN_PNG "Assets\\goldCoin.png"

#define EYE_BOT "Assets\\eyebot.png"
#define HERO_PNG "Assets\\king2.png"
#define VOID_WALKER_PNG "Assets\\voidWalker.png"
#define MAGE_PNG "Assets\\mageClass.png"
#define KNIGHT_PNG "Assets\\knight.png"
#define VOID_WALKER_PNG_SELECTED "Assets\\voidWalker_selected.png"
#define KNIGHT_PNG_SELECTED "Assets\\knight_selected.png"
#define MAGE_PNG_SELECTED "Assets\\mage_selected.png"

#define MOB_LVL_1 "Assets\\eyebot.png"
#define MOB_LVL_2 "Assets\\eyelander.png"

#define LIFE_BONUS_PNG "Assets\\lifeBonus.png"
#define VOID_HOLE_PNG "Assets\\blackHole.png"


#define ARCHERY_BLACK "Assets\\archeryBlack.ttf"
#define TAHOMA "Assets\\TAHOMA.ttf"
#define BALOO "Assets\\baloo.ttf"

#define FILE_PATH_MAP_LEVEL_1 "Assets\\LEVEL1_MAP.txt"
#define FILE_PATH_MAP_LEVEL_2 "Assets\\LEVEL2_MAP.txt"
#define FILE_PATH_MAP_LEVEL_3 "Assets\\LEVEL3_MAP.txt"
//  <----------------------------------------      END DEFINES     ---------------------------------------->







//  <----------------------------------------      OTHER DEFINES     ---------------------------------------->
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


#define LOOPMENU true


#define INSTRUCTIONS_TEXT "Move the hero with w, a, s, d.  Attack the mobs with space and try to collect as many gold coins as possible with a view of increasing your high score. Have fun:) (Press enter to go back to the main menu)"
//  <----------------------------------------      END DEFINES     ---------------------------------------->