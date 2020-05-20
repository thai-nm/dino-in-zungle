#ifndef GAME_BASE_
#define GAME_BASE_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#define SDL_ERROR 1
#define IMG_ERROR 2
#define MIX_ERROR 3
#define TTF_ERROR 4

#define TIME_MAX 1000
#define GROUND 430
#define MAX_HEIGHT 250

#define GROUND_SPEED 5
#define ENEMY_SPEED 5
#define MAX_ENEMY_WIDTH 100

#define IN_AIR_ENEMY 1
#define ON_GROUND_ENEMY 0

#define SLOW_FRAME_CHAR 4
#define SLOW_FRAME_ENEMY 4

#define IS_REPEATITIVE -1
#define NOT_REPEATITIVE 0

using namespace std;


const int SCREEN_WIDTH = 928;
const int SCREEN_HEIGHT = 522;

const string WINDOW_TITLE = "Dino in jungle";

const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 98;
const int RUNNING_FRAMES = 6;
const int FLYING_FRAMES = 5;
const int BACKGROUND_LAYER = 9;

enum ButtonSprite
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_TOTAL = 2
};

void LogError(string msg, int error_code = SDL_ERROR);

#endif // !GAME_LIB_

