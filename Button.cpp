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

void Button::HandleEvent(SDL_Event *e)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = true;
		if (x < position.x)
		{
			inside = false;
		}
		else if (x > position.x + BUTTON_WIDTH)
		{
			inside = false;
		}
		else if (y < position.y)
		{
			inside = false;
		}
		else if (y > position.y + BUTTON_HEIGHT)
		{
			inside = false;
		}
		
		if(inside)
		{
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				currentSprite = BUTTON_MOUSE_OVER;
				break;

			case SDL_MOUSEBUTTONDOWN:
				currentSprite = BUTTON_MOUSE_OVER;
				break;
			
			default:
				currentSprite = BUTTON_MOUSE_OUT;
				break;
			}
		}
	}
}

void Button::Render(SDL_Rect* currentClip[BUTTON_TOTAL], SDL_Renderer* gRenderer, LTexture gButtonTexture)
{
	gButtonTexture.Render(position.x, position.y, gRenderer, currentClip[currentSprite]);
}

ButtonSprite Button::GetCurrentSprite()
{
	return currentSprite;
}
