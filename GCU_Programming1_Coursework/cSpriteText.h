#pragma once
#include "cSprite.h"
#include "GameConstants.h"

class cFont;

class cSpriteText :
	public cSprite
{
private:
	cFont* font;
	SDL_Color color;
	SDL_Color background;
	LPCSTR textureName;
	SDL_Renderer* theRenderer;
public:
	cSpriteText(SDL_Renderer* theRenderer, cFont* font, LPCSTR textureName);
	~cSpriteText();
	void setFont(cFont* font);
	void setColor(SDL_Color c);
	void setText(LPCSTR text);
	void setText(int x, string str = "");
};

