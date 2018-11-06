#include "cSpriteAnimated.h"



cSpriteAnimated::cSpriteAnimated()
{
}


cSpriteAnimated::~cSpriteAnimated()
{
}

void cSpriteAnimated::setTexture(cTextureAnimated * theSpriteTexture)
{
	spriteTexture = theSpriteTexture;
}

void cSpriteAnimated::render(SDL_Renderer * theRenderer, SDL_Rect * theSourceRect, SDL_Rect * theDestRect, FPoint theScaling)
{
	spriteTexture->renderAnimated(theRenderer, theDestRect, theScaling);
}

void cSpriteAnimated::render(SDL_Renderer * theRenderer, SDL_Rect * theSourceRect, SDL_Rect * theDestRect, double rotAngle, SDL_Point * spriteCentre, FPoint theScaling)
{
	spriteTexture->renderAnimated(theRenderer, theDestRect, rotAngle, spriteCentre, theScaling);
}

void cSpriteAnimated::update(double deltaTime)
{
	//Passing update on to the animated texture so it can refresh its animation timer.
	spriteTexture->update(deltaTime);
}
