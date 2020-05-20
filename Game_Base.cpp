#include "Game_Base.h"

void LogError(std::string msg, int error_code)
{
	if (error_code == SDL_ERROR)
	{
		std::cout << msg << SDL_GetError() << std::endl;
	}
	if (error_code == IMG_ERROR)
	{
		std::cout << msg << IMG_GetError() << std::endl;
	}
	if (error_code == MIX_ERROR)
	{
		std::cout << msg << Mix_GetError() << std::endl;
	}
	if (error_code == TTF_ERROR)
	{
		std::cout << msg << TTF_GetError() << std::endl;
	}
}