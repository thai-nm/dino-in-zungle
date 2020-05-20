#include "Game_Utils.h"

void HandlePlayButton(SDL_Event* e, Button &PlayButton, bool& QuitMenu, bool& Play)
{
	if (e->type == SDL_QUIT)
	{
		QuitMenu = true;
	}

	if (PlayButton.IsInside(e))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Play = true;
			QuitMenu = true;
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		}
	}
	else
	{
		PlayButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void HandleHelpButton(SDL_Event* e, SDL_Rect(&gBackButton)[BUTTON_TOTAL], Button& HelpButton, Button& BackButton, LTexture gInstructionTexture, LTexture gBackButtonTexture, SDL_Renderer *gRenderer, bool &Quit_game)
{
	if (HelpButton.IsInside(e))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			HelpButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			HelpButton.currentSprite = BUTTON_MOUSE_OVER;

			bool ReadDone = false;
			while (!ReadDone)
			{
				do
				{
					if (e->type == SDL_QUIT)
					{
						ReadDone = true;
						Quit_game = true;
						Close();
					}

					else if (BackButton.IsInside(e))
					{
						switch (e->type)
						{
						case SDL_MOUSEMOTION:
							BackButton.currentSprite = BUTTON_MOUSE_OVER;
							break;
						case SDL_MOUSEBUTTONDOWN:
							BackButton.currentSprite = BUTTON_MOUSE_OVER;
							ReadDone = true;
							break;
						}
					}
					else
					{
						BackButton.currentSprite = BUTTON_MOUSE_OUT;
					}

					gInstructionTexture.Render(0, 0, gRenderer);

					SDL_Rect* currentClip_Back = &gBackButton[BackButton.currentSprite];
					BackButton.Render(currentClip_Back, gRenderer, gBackButtonTexture);

					SDL_RenderPresent(gRenderer);
				} while (SDL_PollEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION);
			}
			break;
		}
	}
	else
	{
		HelpButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void HandleExitButton(SDL_Event* e, Button& ExitButton, bool& QuitMenu)
{
	if (ExitButton.IsInside(e))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			QuitMenu = true;
			ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		}
	}
	else
	{
		ExitButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

int UpdateGameTime(int& time, int& speed)
{	
	if (time == TIME_MAX)
	{
		speed += 2;
	}

	if (time > TIME_MAX )
	{
		time = 0;
	}
	return ++time;
}

bool AppearanceTime_1(const int &time, const int &enemy_speed)
{
	bool permission = false;
	int moving_time = (SCREEN_WIDTH + MAX_ENEMY_WIDTH) / enemy_speed;

	if (time >= 0 && time <= 0 + moving_time)
	{
		permission = true;
	}
	else if (time >= 220 && time <= 220 + moving_time)
	{
		permission = true;
	}
	else if (time >= 430 && time <= 430 + moving_time)
	{
		permission = true;
	}
	else if (time >= 650 && time <= 650 + moving_time)
	{
		permission = true;
	}

	return permission;
}

bool AppearanceTime_2(const int& time, const int& enemy_speed)
{
	bool permission = false;
	int moving_time = (SCREEN_WIDTH + MAX_ENEMY_WIDTH) / enemy_speed;

	if (time >= 70 && time <= 70 + moving_time)
	{
		permission = true;
	}
	else if (time >= 300 && time <= 300 + moving_time)
	{
		permission = true;
	}
	else if (time >= 550 && time <= 550 + moving_time)
	{
		permission = true;
	}
	else if (time >= 780 && time <= 780 + moving_time)
	{
		permission = true;
	}

	return permission;
}

bool CheckColission(Character character, SDL_Rect* char_clip, Enemy enemy, SDL_Rect* enemy_clip)
{
	bool collide = false;
	
	int left_a = character.GetPosX();
	int right_a = character.GetPosX() + char_clip->w;
	int top_a = character.GetPosY();
	int bottom_a = character.GetPosY() + char_clip->h;

	if (enemy.GetType() == ON_GROUND_ENEMY)
	{
		static const int TRASH_PIXEL_1 = 15;
		static const int TRASH_PIXEL_2 = 30;

		int left_b = enemy.GetPosX();
		int right_b = enemy.GetPosX() + enemy.GetWidth();
		int top_b = enemy.GetPosY();
		int bottom_b = enemy.GetPosY() + enemy.GetHeight();

		if (right_a - TRASH_PIXEL_1 >= left_b && left_a <= right_b)
		{
			if (bottom_a - TRASH_PIXEL_2 >= top_b)
			{
				collide = true;
			}
		}
	}
	else
	{
		static const int TRASH_PIXEL_1 = 30;
		static const int TRASH_PIXEL_2 = 20;
		static const int TRASH_PIXEL_3 = 40;

		int left_b = enemy.GetPosX() + TRASH_PIXEL_1;
		int right_b = enemy.GetPosX() + enemy_clip->w - TRASH_PIXEL_2;
		int top_b = enemy.GetPosY();
		int bottom_b = enemy.GetPosY() + enemy_clip->h - TRASH_PIXEL_3;

		if (right_a >= left_b && left_a <= right_b)
		{
			if (top_a <= bottom_b)
			{
				collide = true;
			}
		}
	}

	return collide;
}

void ControlCharFrame(int &frame)
{
	frame += 1;
	if (frame / SLOW_FRAME_CHAR >= RUNNING_FRAMES)
	{
		frame = 0;
	}
}

void ControlEnemyFrame(int &frame)
{
	frame += 1;
	if (frame / SLOW_FRAME_ENEMY >= FLYING_FRAMES)
	{
		frame = 0;
	}
}
