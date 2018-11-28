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
	this->spriteVisualTexture = NULL;
	this->spriteCollisionTexture = NULL;
	this->spriteCentre = {0, 0};
	this->spriteScale = { 1, 1 };
	this->spriteRotationAngle = 0;

	tint = { 255,255,255,255 };
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

SDL_Point cSprite::getPosition()  // Return the sprites current position
{
	SDL_Point p;
	p.x = transform.x;
	p.y = transform.y;
	return p;
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
	this->spriteVisualTexture = theSpriteTexture;

	// Saving the width and height of the texture for easy access.
	this->textureDimension.w = spriteVisualTexture->getTWidth();
	this->textureDimension.h = spriteVisualTexture->getTHeight();
	// Setting the dimensions of the transform rect depending on the texture size and the scale.
	this->transform.w = (int)textureDimension.w * spriteScale.X;
	this->transform.h = (int)textureDimension.h * spriteScale.Y;
	// Setting the sprite center.
	this->spriteCentre = { this->transform.w / 2, this->transform.h / 2 };

	// Setting the texture to be rendered to the visual texture.
	this->spriteTexture = spriteVisualTexture;

	// Setting the collision texture to the same as the visual texture,
	// if no collision texture has been set explicitly.
	if (spriteCollisionTexture == NULL)
		spriteCollisionTexture = theSpriteTexture;
}

void cSprite::setCollisionTexture(cTexture * theCollisionTexture)
{
	spriteCollisionTexture = theCollisionTexture;
}





void cSprite::render(SDL_Renderer * theRenderer, cCamera * theCamera)
{
	// Using the camera to translate world to screen position and rendering the sprite based on position.
	this->spriteTexture->renderTexture(theRenderer, this->spriteTexture->getTexture(), &textureDimension, &theCamera->WorldToScreen(transform), (double)spriteRotationAngle, &spriteCentre, spriteScale, tint);
}


void cSprite::render(SDL_Renderer* theRenderer, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, FPoint theScaling)
{
	this->spriteTexture->renderTexture(theRenderer, this->spriteTexture->getTexture(), theSourceRect, theDestRect, theScaling, tint);
}


void cSprite::render(SDL_Renderer* theRenderer, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, double rotAngle, SDL_Point* spriteCentre, FPoint theScaling)
{
	this->spriteTexture->renderTexture(theRenderer, this->spriteTexture->getTexture(), theSourceRect, theDestRect, rotAngle, spriteCentre, theScaling, tint);
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
SDL_Rect cSprite::getBoundingBox()
{
	SDL_Rect rect = transform;
	if (rect.w < rect.h)
	{
		rect.w = rect.h;
		rect.x -= getSpriteCentre().x;
	}
	else
	{
		rect.h = rect.w;
		rect.y -= getSpriteCentre().y;
	}
	return rect;
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

void cSprite::setRenderCollision(bool renderCollisionTexture)
{
	if (renderCollisionTexture)
		spriteTexture = spriteCollisionTexture;
	else
		spriteTexture = spriteVisualTexture;
}

bool cSprite::usePixelCollision()
{
	return true;
}

void cSprite::onCollision(fpoint impulse)
{
	cout << "Collision with sprite\n";
}

fpoint cSprite::getImpulse()
{
	return fpoint();
}

bool cSprite::isStatic()
{
	//TODO allow setting static
	return false;
}
