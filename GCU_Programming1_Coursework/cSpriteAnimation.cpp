#include "cSpriteAnimation.h"



int cSpriteAnimation::getCurrentFrame()
{
	return (int)timer % length + startFrame;
}

cSpriteAnimation::cSpriteAnimation()
{
	speed = 30;
	timer = 0.0;
	startFrame = 0;
	length = 1;
}


cSpriteAnimation::~cSpriteAnimation()
{
}

void cSpriteAnimation::render(SDL_Renderer * theRenderer, cCamera * theCamera)
{
	// Getting the target rect from current frame,
	// using the camera to translate world to screen position
	// and calling sprite sheet to render the sprite.
	cSpriteSheet::render(theRenderer, getCurrentFrame(), &theCamera->WorldToScreen(transform), (double)spriteRotationAngle, &spriteCentre, spriteScale);
}

void cSpriteAnimation::render(SDL_Renderer * theRenderer, SDL_Rect * theDestRect, FPoint theScaling)
{
	cSpriteSheet::render(theRenderer, getCurrentFrame(), theDestRect, theScaling);
}

void cSpriteAnimation::render(SDL_Renderer * theRenderer, SDL_Rect * theDestRect, double rotAngle, SDL_Point * spriteCentre, FPoint theScaling)
{
	cSpriteSheet::render(theRenderer, getCurrentFrame(), theDestRect, rotAngle, spriteCentre, theScaling);
}

void cSpriteAnimation::play()
{
	isPlaying = true;
}

void cSpriteAnimation::pause()
{
	isPlaying = false;
}

void cSpriteAnimation::reset()
{
	timer = 0;
}

void cSpriteAnimation::update(double deltaTime)
{
	timer += deltaTime * speed;
}

void cSpriteAnimation::trim(int animStartFrame, int animLength)
{
	startFrame = animStartFrame;
	length = animLength;
}

void cSpriteAnimation::setSpeed(float framesPerSecond)
{
	speed = framesPerSecond;
}

