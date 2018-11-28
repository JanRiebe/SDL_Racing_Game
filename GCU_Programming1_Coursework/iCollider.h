#pragma once
#include "GameConstants.h"

class cCamera;

class iCollider
{
public:

	// Returns whether this collider moves.
	virtual bool isStatic() = 0;

	// Returns whether pixelPerfect collision should be checked for this collider. Else bounding box collision is used.
	virtual bool usePixelCollision() = 0;

	// Returns the bounding box in world coordinates, which is always a square with the longer side of the transform dimensions as width and height.
	virtual SDL_Rect getBoundingBox() = 0;

	// Used in pixel perfect collision to render the collision texture onto the render target that will be checked for overlapping pixels.
	virtual void render(SDL_Renderer* theRenderer, cCamera* theCamera) = 0;

	// Used in pixel perfect collision to switch the rendering mode of the collider to the collision texture.
	virtual void setRenderCollision(bool renderCollisionTexture) = 0;

	// Called by the collision manager when this has collided with another collider.
	virtual void onCollision(fpoint impulse) = 0;

	// Call this to recieve the impulse the collider would send to another collider on collision.
	virtual fpoint getImpulse() = 0;
};

