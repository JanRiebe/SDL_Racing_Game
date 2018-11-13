/*
=================
cSprite.h
- Header file for class definition - SPECIFICATION
- Header file for the Sprite class
=================
*/
#ifndef _CSPRITE_H
#define _CSPRITE_H

#include "cTextureMgr.h"
#include "cTexture.h"
#include "cCamera.h"


class cSprite
{
protected:
	// position
	SDL_Rect transform;
	SDL_Point spriteCentre;
	FPoint spriteScale;
	float spriteRotationAngle;

	// Pointer to Sprite Texture
	cTexture* spriteTexture;

	// Texture width & Height
	SDL_Rect textureDimension;


public:
	cSprite();			// Default constructor
	cSprite(cTexture* theSpriteTexture);			// Default constructor
	~cSprite();			// Destructor
	// Renders this sprite based on the internal variables spritePos_2D, spriteScale and spriteRotationAngle. This should be overwritten by subclasses and used in general for rendering. 
	virtual void render(SDL_Renderer* theRenderer, cCamera* theCamera);
	void render(SDL_Renderer* theRenderer, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, FPoint theScaling);
	void render(SDL_Renderer* theRenderer, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, double rotAngle, SDL_Point* spriteCentre, FPoint theScaling);
	SDL_Rect getSpritePos();  // Return the sprites current position
	void setSpritePos(SDL_Point sPosition); // set the position of the sprite
	cTexture* getTexture();  // Return the sprites current image
	void setTexture(cTexture* theSpriteTexture);  // set the image of the sprite
	void setSpriteDimensions(int texWidth, int textHeight);
	SDL_Rect getSpriteDimensions(); // Return sprite dimensions
	SDL_Point getSpriteCentre();  // Return the sprites current position
	void setSpriteCentre(SDL_Point sCentre); // set the position of the sprite
	FPoint getSpriteScale();  // Return the sprites scaling factor
	void setSpriteScale(FPoint sScale); // set the sprites scaling factor
	void scaleSprite(); // update the sprites width & height
	float getSpriteRotAngle();  // Return the sprites rotation angle
	void setSpriteRotAngle(float angle); // set the sprites rotation angle

	virtual void update(double deltaTime) {};
};
#endif