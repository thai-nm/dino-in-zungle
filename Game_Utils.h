#ifndef GAME_UTILS_H_
#define GAME_UTILS_H_

#include "Game_Base.h"
#include "Enemy.h"
#include "Character.h"

bool Init();

bool LoadMedia();

void Close();

int UpdateGameTime(int &time,int &speed);

bool AppearanceTime_1(const int& time, const int& enemy_speed);

bool AppearanceTime_2(const int& time, const int& enemy_speed);

bool CheckColission(Character character, SDL_Rect* char_clip, Enemy enemy, SDL_Rect* enemy_clip = nullptr);

void ControlCharFrame(int &frame);

void ControlEnemyFrame(int &frame);

#endif // !GAME_UTILS_H_

