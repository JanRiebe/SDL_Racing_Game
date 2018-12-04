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
#include "iCollider.h"

class cCollider;

class cSprite:
	public iCollider
{
protected:
	// position
	SDL_Rect transform;
	SDL_Point spriteCentre;
	FPoint spriteScale;
	float spriteRotationAngle;

	// Pointer to the texture that will be rendered
	cTexture* spriteTexture;
	// Pointer to the texture that is displayed to the player
	cTexture* spriteVisualTexture;
	// Pointer to the texture that is used in collision detection
	cTexture* spriteCollisionTexture;

	// Texture width & Height
	SDL_Rect textureDimension;

	// Allows rending the texture of this sprite in a tint, without affecting the texture for other sprites.
	SDL_Color tint;

	CollisionMessage collMessage;
	bool collisionStatic;

public:
	cSprite();			// Default constructor
	cSprite(cTexture* theSpriteTexture);			// Default constructor
	~cSprite();			// Destructor
	// Renders this sprite based on the internal variables spritePos_2D, spriteScale and spriteRotationAngle. This should be overwritten by subclasses and used in general for rendering. 
	virtual void render(SDL_Renderer* theRenderer, cCamera* theCamera);
	void render(SDL_Renderer* theRenderer, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, FPoint theScaling);
	void render(SDL_Renderer* theRenderer, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, double rotAngle, SDL_Point* spriteCentre, FPoint theScaling);
	// Renders the collision texture instead of the visual texture
	SDL_Point getPosition();  // Return the sprites current position
	void setSpritePos(SDL_Point sPosition); // set the position of the sprite
	cTexture* getTexture();  // Return the sprites current image
	void setTexture(cTexture* theSpriteTexture);  // set the image of the sprite
	void setCollisionTexture(cTexture* theCollisionTexture);  // set the collision texture, which is used for checking pixel perfect collision
	void setSpriteDimensions(int texWidth, int textHeight);
	SDL_Rect getSpriteDimensions(); // Return sprite dimensions
	SDL_Point getSpriteCentre();  // Return the sprites current position
	void setSpriteCentre(SDL_Point sCentre); // set the position of the sprite
	FPoint getSpriteScale();  // Return the sprites scaling factor
	virtual void setSpriteScale(FPoint sScale); // set the sprites scaling factor
	void scaleSprite(); // update the sprites width & height
	float getSpriteRotAngle();  // Return the sprites rotation angle
	void setSpriteRotAngle(float angle); // set the sprites rotation angle
	
	// iCollider
	// Returns the bounding box in world coordinates, which is always a square with the longer side of the transform dimensions as width and height.
	virtual SDL_Rect getBoundingBox();		
	// Sets the texture to be rendered to either the collision texture or the visual texture, depending on the parameter.
	void setRenderCollision(bool renderCollisionTexture);
	bool usePixelCollision();		// Returns whether pixelPerfect collision should be checked for this sprite. Else bounding box collision is used.
	// Called by the collision manager when this has collided with another sprite.
	virtual void onCollision(CollisionMessage message = COLLISION, fpoint impulse = { 0,0 });
	// Returns the impulse. For normal sprites the returned fpoint has the values 0, 0.
	virtual fpoint getImpulse();
	// Returns whether this collider moves.
	virtual bool isStatic();
	// Get the message that this collider sends to other colliders on collision. Overwrite this to define specific messages.
	virtual CollisionMessage getCollisionMessage();
	virtual void setCollisionMessage(CollisionMessage m);

	void setStatic(bool st);


	// Overwrite this to add per frame behaviour.
	virtual void update(double deltaTime) {};

};
#endif