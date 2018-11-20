#pragma once
#include "GameConstants.h"

class cCollider;

class ICollidable
{
protected:
	cCollider* collider;
	float radius;

public:
	ICollidable();
	~ICollidable();
	// Sets the collider.
	void setCollider(cCollider* c);
	// Returns the collider attached to this, NULL if no collider is attached.
	cCollider* getCollider();

	// Returns the world position.
	virtual SDL_Point getCenter() = 0;
	// Returns the collsion radius for broad phase collision.
	virtual float getRadius() = 0;
	// Called by the collision manager when this has collided with another ICollidable.
	virtual void onCollision(fpoint impulse) = 0;
	// Overwrite this to update the collider.
	virtual void updateCollider() = 0;
	// Overwrite this to return the impulse this has in this moment.
	virtual fpoint getImpulse() = 0;

};

