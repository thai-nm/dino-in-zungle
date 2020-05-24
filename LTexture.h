#ifndef LTEXTURE_H_
#define LTEXTURE_H_

#include "Game_Base.h"

class LTexture
{
public:
	LTexture();

	~LTexture();

	void Free();

	bool LoadFromRenderedText(std::string textureText, TTF_Font* gFont, SDL_Color textColor, SDL_Renderer* gRenderer);

	bool LoadFromFile(std::string path, SDL_Renderer *gRenderer);

	void Render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = nullptr);

	int GetWidth();

	int GetHeight();

private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};

#endif // !LTEXTURE_H_