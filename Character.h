#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "LTexture.h"

#define JUMP 1
#define FALL 2
#define RUN	0

class Character
{
public:
	static const int JUMP_SPEED = 8;
	static const int FALL_SPEED = 8;

	Character();

	bool OnGround();

	void HandleEvent(SDL_Event& e, Mix_Chunk *gJump);

	void Move();

	void Render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, LTexture gCharacterTexture);

	int GetPosX();

	int GetPosY();

private:
	int posX, posY;

	int status;
};

#endif // !CHARACTER_H_