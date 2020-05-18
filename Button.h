#ifndef BUTTON_H_
#define BUTTON_H_

#include "Game_Base.h"
#include "LTexture.h"

class Button
{
public:
	Button();

	Button(int x, int y);

	void HandleEvent(SDL_Event* e);

	void Render(SDL_Rect* currentClip[BUTTON_TOTAL], SDL_Renderer* gRenderer, LTexture gButtonTexture);

	ButtonSprite GetCurrentSprite();
private:
	SDL_Point position;

	ButtonSprite currentSprite;
};

#endif // !BUTTON_H_

