#include "Game_Base.h"
#include "Game_Utils.h"
#include "LTexture.h"
#include "Button.h"
#include "Character.h"
#include "Enemy.h"

void renderScrollingBackground(vector <double>& scrollingOffset);

void renderScrollingGround(int& speed, const int acceleration);

const string LAYER[BACKGROUND_LAYER] = {
	"imgs/background/layer01.png",
	"imgs/background/layer02.png",
	"imgs/background/layer03.png",
	"imgs/background/layer04.png",
	"imgs/background/layer05.png",
	"imgs/background/layer06.png",
	"imgs/background/layer07.png",
	"imgs/background/layer08.png",
	"imgs/background/layer09.png",
};

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
Mix_Music* gMusic = nullptr;

SDL_Rect gPlayButton[BUTTON_TOTAL];
SDL_Rect gHelpButton[BUTTON_TOTAL];
SDL_Rect gExitButton[BUTTON_TOTAL];
SDL_Rect gCharacterClips[RUNNING_FRAMES];
SDL_Rect gEnemyClips[FLYING_FRAMES];

LTexture gMenuTexture;
LTexture gBackgroundTexture[BACKGROUND_LAYER];
LTexture gCharacterTexture;
LTexture gGroundTexture;
LTexture gPlayButtonTexture;
LTexture gHelpButtonTexture;
LTexture gExitButtonTexture;

Button PlayButton(389, 186);
Button HelpButton(389, 293);
Button ExitButton(389, 402);

Character character;

Enemy enemy1(ON_GROUND_ENEMY);
Enemy enemy2(ON_GROUND_ENEMY);
Enemy enemy3(IN_AIR_ENEMY);

int main(int argc, char* argv[])
{
	if (!Init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!LoadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool Quit_Menu = false;
			bool PlayAgain = false;

			while (!Quit_Menu)
			{
				SDL_Event e_mouse;
				gMenuTexture.Render(0, 0, gRenderer);
				while (SDL_PollEvent(&e_mouse) != 0)
				{
					if (e_mouse.type == SDL_QUIT)
					{
						Quit_Menu = true;
					}

					if (PlayButton.IsInside(&e_mouse))
					{
						switch (e_mouse.type)
						{
						case SDL_MOUSEMOTION:
							cout << "insided play" << endl;
							PlayButton.currentSprite = BUTTON_MOUSE_OVER;
							break;
						case SDL_MOUSEBUTTONDOWN:
							PlayAgain = true;
							Quit_Menu = true;
							PlayButton.currentSprite = BUTTON_MOUSE_OVER;
							break;
						}
					}
					else
					{
						PlayButton.currentSprite = BUTTON_MOUSE_OUT;
					}

					if (HelpButton.IsInside(&e_mouse))
					{
						switch (e_mouse.type)
						{
						case SDL_MOUSEMOTION:
							cout << "inside help" << endl;
							HelpButton.currentSprite = BUTTON_MOUSE_OVER;
							break;
						case SDL_MOUSEBUTTONDOWN:
							HelpButton.currentSprite = BUTTON_MOUSE_OVER;
							break;
						}
					}
					else
					{
						HelpButton.currentSprite = BUTTON_MOUSE_OUT;
					}

					if (ExitButton.IsInside(&e_mouse))
					{
						switch (e_mouse.type)
						{
						case SDL_MOUSEMOTION:
							cout << "inside exit" << endl;
							ExitButton.currentSprite = BUTTON_MOUSE_OVER;
							break;
						case SDL_MOUSEBUTTONDOWN:
							Quit_Menu = true;
							ExitButton.currentSprite = BUTTON_MOUSE_OVER;
							break;
						}
					}
					else
					{
						ExitButton.currentSprite = BUTTON_MOUSE_OUT;
					}
				}

				SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];
				PlayButton.Render(currentClip_Play, gRenderer, gPlayButtonTexture);

				SDL_Rect* currentClip_Help = &gHelpButton[HelpButton.currentSprite];
				HelpButton.Render(currentClip_Help, gRenderer, gHelpButtonTexture);

				SDL_Rect* currentClip_Exit = &gExitButton[ExitButton.currentSprite];
				ExitButton.Render(currentClip_Exit, gRenderer, gExitButtonTexture);

				SDL_RenderPresent(gRenderer);
			}

			while (PlayAgain)
			{
				srand(time(NULL));
				int time = 0;
				int acceleration = 0;

				int OffsetSpeed_Ground = 0;
				vector <double> OffsetSpeed_Bkgr(BACKGROUND_LAYER, 0);

				int frame_Character = 0;
				int frame_Enemy = 0;

				SDL_Event e;
				//Mix_PlayMusic(gMusic, -1);
				bool quit = false;

				while (!quit)
				{
					UpdateGameTime(time, acceleration);

					while (SDL_PollEvent(&e) != 0)
					{
						if (e.type == SDL_QUIT)
						{
							quit = true;
						}

						character.HandleEvent(e);
					}
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(gRenderer);


					renderScrollingBackground(OffsetSpeed_Bkgr);
					renderScrollingGround(OffsetSpeed_Ground, acceleration);

					character.Move();
					SDL_Rect* currentClip_Character = nullptr;
					if (character.OnGround())
					{
						currentClip_Character = &gCharacterClips[frame_Character / SLOW_FRAME_CHAR];
						character.Render(currentClip_Character, gRenderer, gCharacterTexture);
					}
					else
					{
						currentClip_Character = &gCharacterClips[0];
						character.Render(currentClip_Character, gRenderer, gCharacterTexture);
					}

					if (AppearanceTime_1(time, enemy1.GetSpeed(acceleration)))
					{
						enemy1.Move(acceleration);
						enemy1.Render(gRenderer);
					}
					if (AppearanceTime_2(time, enemy1.GetSpeed(acceleration)))
					{
						enemy2.Move(acceleration);
						enemy2.Render(gRenderer);
					}

					SDL_Rect* currentClip_Enemy = &gEnemyClips[frame_Enemy / 4];
					enemy3.Move(acceleration);
					enemy3.Render(gRenderer, currentClip_Enemy);


					if (CheckColission(character, currentClip_Character, enemy1))
					{
						cout << "Crash 1!" << endl;
						quit = true;
					}
					if (CheckColission(character, currentClip_Character, enemy2))
					{
						cout << "Crash 2!" << endl;
						quit = true;
					}
					if (CheckColission(character, currentClip_Character, enemy3, currentClip_Enemy))
					{
						quit = true;
					}


					SDL_RenderPresent(gRenderer);

					ControlCharFrame(frame_Character);
					ControlEnemyFrame(frame_Enemy);
					cout << time << endl;
				}

				cout << "Do you want to play again?" << endl;
				int check;
				cin >> check;
				if (check == 1)
				{
					Close();
					PlayAgain = true;
				}
				else
				{
					PlayAgain = false;
				}
				Close();
			}
		}
	}
	Close();

	return 0;
}


void renderScrollingBackground(vector <double>& offsetSpeed)
{
	vector <double> layer_speed;
	layer_speed.push_back(0.0);
	layer_speed.push_back(0.25);
	layer_speed.push_back(0.5);
	layer_speed.push_back(0.75);
	layer_speed.push_back(1.0);
	layer_speed.push_back(1.25);
	layer_speed.push_back(1.5);
	layer_speed.push_back(1.75);
	layer_speed.push_back(2.0);

	for (int i = 0; i < BACKGROUND_LAYER; ++i)
	{
		offsetSpeed[i] -= layer_speed[i];
		if (offsetSpeed[i] < -gBackgroundTexture[i].GetWidth())
		{
			offsetSpeed[i] = 0;
		}
		gBackgroundTexture[i].Render(offsetSpeed[i], 0, gRenderer);
		gBackgroundTexture[i].Render(offsetSpeed[i] + gBackgroundTexture[i].GetWidth(), 0, gRenderer);
	}
}

void renderScrollingGround(int& speed, const int acceleration)
{
	speed -= GROUND_SPEED + acceleration;
	if (speed < -gGroundTexture.GetWidth())
	{
		speed = 0;
	}
	gGroundTexture.Render(speed, 0, gRenderer);
	gGroundTexture.Render(speed + gGroundTexture.GetWidth(), 0, gRenderer);
}

bool Init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO) < 0)
	{
		LogError("Can not initialize SDL.", SDL_ERROR);
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cout << "Warning: Linear texture filtering not enabled!";
		}

		gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			LogError("Can not create window", SDL_ERROR);
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				LogError("Can not create renderer", SDL_ERROR);
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					LogError("Can not initialize SDL_image", IMG_ERROR);
					success = false;
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool LoadMedia()
{
	bool success = true;

	gMusic = Mix_LoadMUS("sound/bkgr_audio.wav");
	if (gMusic == nullptr)
	{
		LogError("Failed to load background music", MIX_ERROR);
		success = false;
	}
	else
	{
		if (!gMenuTexture.LoadFromFile("imgs/background/menu.png", gRenderer))
		{
			cout << "Failed to load menu image" << endl;
			success = false;
		}

		if (!gPlayButtonTexture.LoadFromFile("imgs/button/big_button/play_button.png", gRenderer))
		{
			cout << "Failed to load play_button image" << endl;
			success = false;
		}
		else
		{
			for (int i = 0; i < BUTTON_TOTAL; ++i)
			{
				gPlayButton[i].x = 150*i;
				gPlayButton[i].y = 0;
				gPlayButton[i].w = 150;
				gPlayButton[i].h = 98;
			}
		}

		if (!gHelpButtonTexture.LoadFromFile("imgs/button/big_button/help_button.png", gRenderer))
		{
			cout << "Failed to load help_button image" << endl;
			success = false;
		}
		else
		{
			for (int i = 0; i < BUTTON_TOTAL; ++i)
			{
				gHelpButton[i].x = 150 * i;
				gHelpButton[i].y = 0;
				gHelpButton[i].w = 150;
				gHelpButton[i].h = 98;
			}
		}

		if (!gExitButtonTexture.LoadFromFile("imgs/button/big_button/exit_button.png", gRenderer))
		{
			cout << "Failed to load exit_button image" << endl;
			success = false;
		}
		else
		{
			for (int i = 0; i < BUTTON_TOTAL; ++i)
			{
				gExitButton[i].x = 150 * i;
				gExitButton[i].y = 0;
				gExitButton[i].w = 150;
				gExitButton[i].h = 98;
			}
		}

		for (int i = 0; i < BACKGROUND_LAYER; ++i)
		{
			if (!gBackgroundTexture[i].LoadFromFile(LAYER[i].c_str(), gRenderer))
			{
				cout << "Failed to load background image" << endl;
				success = false;
			}
		}

		if (!gGroundTexture.LoadFromFile("imgs/background/ground.png", gRenderer))
		{
			cout << "Failed to load ground image" << endl;
			success = false;
		}

		if (!gCharacterTexture.LoadFromFile("imgs/character/char_run.png", gRenderer))
		{
			cout << "Failed to load character_run image." << endl;
			success = false;
		}
		else
		{
			gCharacterClips[0].x = 57*0;
			gCharacterClips[0].y = 0;
			gCharacterClips[0].w = 57;
			gCharacterClips[0].h = 57;

			gCharacterClips[1].x = 57*1;
			gCharacterClips[1].y = 0;
			gCharacterClips[1].w = 57;
			gCharacterClips[1].h = 57;

			gCharacterClips[2].x = 57*2;
			gCharacterClips[2].y = 0;
			gCharacterClips[2].w = 57;
			gCharacterClips[2].h = 57;

			gCharacterClips[3].x = 57*3;
			gCharacterClips[3].y = 0;
			gCharacterClips[3].w = 57;
			gCharacterClips[3].h = 57;

			gCharacterClips[4].x = 57*4;
			gCharacterClips[4].y = 0;
			gCharacterClips[4].w = 57;
			gCharacterClips[4].h = 57;

			gCharacterClips[5].x = 57*5;
			gCharacterClips[5].y = 0;
			gCharacterClips[5].w = 57;
			gCharacterClips[5].h = 57;
		}

		if (!enemy1.LoadFromFile("imgs/enemy/cactus.png", gRenderer))
		{
			cout << "Failed to load enemy1 image." << endl;
			success = false;
		}

		if (!enemy2.LoadFromFile("imgs/enemy/cactus.png", gRenderer))
		{
			cout << "Failed to load enemy2 image." << endl;
			success = false;
		}

		if (!enemy3.LoadFromFile("imgs/enemy/bat.png", gRenderer))
		{
			cout << "Failed to load bat enemy image." << endl;
			success = false;
		}
		else
		{
			gEnemyClips[0].x = 43*3;
			gEnemyClips[0].y = 0;
			gEnemyClips[0].w = 43;
			gEnemyClips[0].h = 30;

			gEnemyClips[1].x = 43 * 4;
			gEnemyClips[1].y = 0;
			gEnemyClips[1].w = 43;
			gEnemyClips[1].h = 30;

			gEnemyClips[2].x = 43*2;
			gEnemyClips[2].y = 0;
			gEnemyClips[2].w = 43;
			gEnemyClips[2].h = 30;

			gEnemyClips[3].x = 43;
			gEnemyClips[3].y = 0;
			gEnemyClips[3].w = 43;
			gEnemyClips[3].h = 30;

			gEnemyClips[4].x = 0;
			gEnemyClips[4].y = 0;
			gEnemyClips[4].w = 43;
			gEnemyClips[4].h = 30;
		}
	}
	return success;
}

void Close()
{
	gCharacterTexture.Free();
	gMenuTexture.Free();
	gCharacterTexture.Free();
	gGroundTexture.Free();
	gPlayButtonTexture.Free();
	gHelpButtonTexture.Free();
	gExitButtonTexture.Free();

	for (int i = 0; i < BACKGROUND_LAYER; ++i)
	{
		gBackgroundTexture[i].Free();
	}

	Mix_FreeMusic(gMusic);
	gMusic = nullptr;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}
