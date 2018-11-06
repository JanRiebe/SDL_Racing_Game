#pragma once
#include "cSprite.h"
#include "cTextureAnimated.h"

class cSpriteAnimated :
	public cSprite
{
private:
	//Overwriting the type of spriteTexture
	cTextureAnimated* spriteTexture;

public:
	cSpriteAnimated();
	~cSpriteAnimated();

	//Overwriting so that a cTextureAnimated is set instead of a cTexture
	void setTexture(cTextureAnimated* theSpriteTexture);

	//Overwriting render to call renderAnimated on the animated texture instead of normal render
	void render(SDL_Renderer* theRenderer, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, FPoint theScaling);
	void render(SDL_Renderer* theRenderer, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, double rotAngle, SDL_Point* spriteCentre, FPoint theScaling);

	void update(double deltaTime);
};




//TODO how to switch between animations?