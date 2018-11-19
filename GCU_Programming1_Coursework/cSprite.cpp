/*
=================
cSprite.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cSprite.h"
/*
=================
- Data constructor initializes the cSprite to the data passed to
- the constructor from the paramater sPosition.
- Is always called, thus ensures all sprite objects are in a consistent state.
=================
*/
cSprite::cSprite() 			// Default constructor
{

	this->transform = { 0, 0, 0, 0 };
	this->spriteTexture = NULL;
	this->spriteCentre = {0, 0};
	this->spriteScale = { 1, 1 };
	this->spriteRotationAngle = 0;
}

cSprite::cSprite(cTexture* theSpriteTexture) 			// Default constructor
{
	this->spriteTexture = theSpriteTexture;
	this->setSpriteDimensions(this->spriteTexture->getTWidth(), this->spriteTexture->getTHeight());
	this->transform = { 0, 0, this->spriteTexture->getTWidth(), this->spriteTexture->getTHeight() };
	this->spriteCentre = { this->transform.w / 2, this->transform.h / 2};
	this->spriteScale = { 1, 1 };
	this->spriteRotationAngle = 0;
}

/*
=================
- Destructor
=================
*/
cSprite::~cSprite()			// Destructor
{
}
/*
=================
- Return the sprites current position.
=================
*/

SDL_Rect cSprite::getSpritePos()  // Return the sprites current position
{
	return this->transform;
}

/*
=================
- set the position of the sprite.
=================
*/

void cSprite::setSpritePos(SDL_Point sPosition)  // set the position of the sprite
{
	this->transform.x = sPosition.x;
	this->transform.y = sPosition.y;
}

/*
=================
- Return the sprites current image.
=================
*/

cTexture* cSprite::getTexture()  // Return the sprites current image
{
	return this->spriteTexture;
}

/*
=================
- set the image of the sprite.
=================
*/

void cSprite::setTexture(cTexture* theSpriteTexture)  // set the image of the sprite
{
	this->spriteTexture = theSpriteTexture;

	// Saving the width and height of the texture for easy access.
	this->textureDimension.w = spriteTexture->getTWidth();
	this->textureDimension.h = spriteTexture->getTHeight();
	// Setting the dimensions of the transform rect depending on the texture size and the scale.
	this->transform.w = (int)textureDimension.w * spriteScale.X;
	this->transform.h = (int)textureDimension.h * spriteScale.Y;
	// Setting the sprite center.
	this->spriteCentre = { this->transform.w / 2, this->transform.h / 2 };
}



void cSprite::render(SDL_Renderer * theRenderer, cCamera * theCamera)
{
	// Using the camera to translate world to screen position and rendering the sprite based on position.
	this->spriteTexture->renderTexture(theRenderer, this->spriteTexture->getTexture(), &textureDimension, &theCamera->WorldToScreen(transform), (double)spriteRotationAngle, &spriteCentre, spriteScale);
}


void cSprite::render(SDL_Renderer* theRenderer, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, FPoint theScaling)
{
	this->spriteTexture->renderTexture(theRenderer, this->spriteTexture->getTexture(), theSourceRect, theDestRect, theScaling);
}


void cSprite::render(SDL_Renderer* theRenderer, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, double rotAngle, SDL_Point* spriteCentre, FPoint theScaling)
{

	this->spriteTexture->renderTexture(theRenderer, this->spriteTexture->getTexture(), theSourceRect, theDestRect, rotAngle, spriteCentre, theScaling);
}


/*
=================
- Set the sprite dimensions.
=================
*/

void cSprite::setSpriteDimensions(int width, int height)
{
	this->transform.w = width;
	this->transform.h = height;
}


/*
=================
- Get the sprite dimensions.
=================
*/
SDL_Rect cSprite::getSpriteDimensions()
{
	return this->transform;
}
/*
=================
- Return the sprite centre.
=================
*/

SDL_Point cSprite::getSpriteCentre()  // Return the sprites current position
{
	return this->spriteCentre;
}

/*
=================
- set the the sprite centre.
=================
*/

void cSprite::setSpriteCentre(SDL_Point sCentre)  // set the position of the sprite
{
	this->spriteCentre.x = sCentre.x;
	this->spriteCentre.y = sCentre.y;
}
/*
=================
- Return the sprite scaling.
=================
*/

FPoint cSprite::getSpriteScale()  // Return the sprites current scaling
{
	return this->spriteScale;
}

/*
=================
- set the the sprite scale.
=================
*/

void cSprite::setSpriteScale(FPoint sScale)  // set the sprites current scaling
{
	this->spriteScale.X = sScale.X;
	this->spriteScale.Y = sScale.Y;
	// Updating the transforms based on the new scale.
	scaleSprite();
}
/*
=================
- Update sprite scale.
=================
*/

void cSprite::scaleSprite()  // set the sprites current scaling
{
	// Scale sprite
	this->transform.w = (int)(this->textureDimension.w * this->spriteScale.X);
	this->transform.h = (int)(this->textureDimension.h * this->spriteScale.Y);
	// Scale Sprite Centre for rotation.
	this->spriteCentre.x = this->transform.w / 2;
	this->spriteCentre.y = this->transform.h / 2;
}
/*
=================
- Return the sprite rotation Angle.
=================
*/

float cSprite::getSpriteRotAngle()  // Return the sprites current scaling
{
	return this->spriteRotationAngle;
}

/*
=================
- set the the sprite scale.
=================
*/

void cSprite::setSpriteRotAngle(float angle)  // set the sprites current scaling
{
	this->spriteRotationAngle = angle;
}