#include "Game_Utils.h"

/*void HandlePlayButton(SDL_Event* e, Button PlayButton, bool& QuitMenu, bool& Play)
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
}*/

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
				cout << "Left a: " << left_a << endl
					<< "Right a: " << right_a << endl
					<< "Top a: " << top_a << endl
					<< "Bot a: " << bottom_a << endl;

				cout << "Left b: " << left_b << endl
					<< "Right b: " << right_b << endl
					<< "Top b: " << top_b << endl
					<< "Bot b: " << bottom_b << endl;
				cout << "Crash 3!" << endl << endl;
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
