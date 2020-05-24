#include "Button.h"

Button::Button()
{
	position.x = 0;
	position.y = 0;

	currentSprite = BUTTON_MOUSE_OUT;
}

Button::Button(int x, int y)
{
	position.x = x;
	position.y = y;

	currentSprite = BUTTON_MOUSE_OUT;
}

void Button::SetPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

bool Button::IsInside(SDL_Event *e, int size)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		int button_width, button_height;
		if (size == SMALL_BUTTON)
		{
			button_width = SMALL_BUTTON_WIDTH;
			button_height = SMALL_BUTTON_HEIGHT;
		}
		else
		{
			button_width = COMMON_BUTTON_WIDTH;
			button_height = COMMON_BUTTON_HEIGHT;
		}

		SDL_GetMouseState(&x, &y);

		bool inside = true;
		if (x < position.x)
		{
			inside = false;
		}
		else if (x > position.x + button_width)
		{
			inside = false;
		}
		else if (y < position.y)
		{
			inside = false;
		}
		else if (y > position.y + button_height)
		{
			inside = false;
		}
		return inside;
	}
	return false;
}

void Button::Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gButtonTexture)
{
	gButtonTexture.Render(position.x, position.y, gRenderer, currentClip);
}