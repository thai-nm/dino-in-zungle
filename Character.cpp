#include "Character.h"

Character::Character()
{
	posX = SCREEN_WIDTH - 700;
	posY = GROUND;

	status = 0;
}

bool Character::OnGround()
{
	return posY == GROUND;
}

void Character::HandleEvent(SDL_Event& e, Mix_Chunk *gJump)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_UP:
			{
				if (OnGround())
				{
					Mix_PlayChannel(MIX_CHANNEL, gJump, NOT_REPEATITIVE);
					status = JUMP;
				}
			}
		}
	}
}

void Character::Move()
{
	if (status == JUMP && posY >= MAX_HEIGHT)
	{
		posY += -JUMP_SPEED;
	}
	if (posY <= MAX_HEIGHT)
	{
		status = FALL;
	}
	if (status == FALL && posY < GROUND)
	{
		posY += FALL_SPEED;
	}
}

void Character::Render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, LTexture gCharacterTexture)
{
	gCharacterTexture.Render(posX, posY, gRenderer, currentClip);
}

int Character::GetPosX()
{
	return posX;
}

int Character::GetPosY()
{
	return posY;
}