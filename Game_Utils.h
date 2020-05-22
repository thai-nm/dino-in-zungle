#ifndef GAME_UTILS_H_
#define GAME_UTILS_H_

#include "Game_Base.h"
#include "Button.h"
#include "Enemy.h"
#include "Character.h"

bool Init();
bool LoadMedia();
void Close();

void HandlePlayButton(SDL_Event *e, Button &PlayButton, bool& QuitMenu, bool& Play);

void HandleHelpButton(SDL_Event* e, SDL_Rect(&gBackButton)[BUTTON_TOTAL], Button& HelpButton, Button& BackButton, LTexture gInstructionTexture, LTexture gBackButtonTexture, SDL_Renderer* gRenderer, bool& Quit_game);

void HandleExitButton(SDL_Event* e, Button& ExitButton, bool& Quit);

void HandlePauseButton(SDL_Event* e, SDL_Renderer* gRenderer, SDL_Rect(&gContinueButton)[BUTTON_TOTAL], Button& PauseButton, Button ContinueButton, LTexture gContinueButtonTexture, bool &game_state);

void HandlePlayAgainButton();

void GenerateEnemy(Enemy &enemy1, Enemy &enemy2, Enemy &enemy3, SDL_Rect (&gEnemyClips)[FLYING_FRAMES], SDL_Renderer *gRenderer);

int UpdateGameTime(int &time,int &speed);

bool AppearanceTime_1(const int& time, const int& enemy_speed);

bool AppearanceTime_2(const int& time, const int& enemy_speed);

bool CheckColission(Character character, SDL_Rect* char_clip, Enemy enemy, SDL_Rect* enemy_clip = nullptr);

void ControlCharFrame(int &frame);

void ControlEnemyFrame(int &frame);

#endif // !GAME_UTILS_H_

