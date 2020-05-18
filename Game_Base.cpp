#include "Game_Base.h"

void LogError(string msg, int error_code)
{
	if (error_code == SDL_ERROR)
	{
		cout << msg << SDL_GetError() << endl;
	}
	if (error_code == IMG_ERROR)
	{
		cout << msg << IMG_GetError() << endl;
	}
	if (error_code == MIX_ERROR)
	{
		cout << msg << Mix_GetError() << endl;
	}
	if (error_code == TTF_ERROR)
	{
		cout << msg << TTF_GetError() << endl;
	}
}