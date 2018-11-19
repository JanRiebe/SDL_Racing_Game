#pragma once
#include "gameHeaders.h"

class cCollider
{
private:
	float lastRotationAngle;
public:
	cCollider();
	~cCollider();
	// The bounding box of this collider.
	SDL_Rect bBox;
	// The primitives this collider is comprised of.
	vector<SDL_Rect*> collisionPrimitives;
	// Rotates all primitives to the given angle.
	void rotate(float angle);
	// Called by the collision manager when this collider collides with another.
	virtual void onCollision(cCollider* other) = 0;
	// Overwrite this to allow access to this collider's velocity.
	virtual fpoint getVelocity() = 0;
	// Overwrite this to allow access to this collider's mass.
	virtual float getMass() = 0;
	// Overwrite this to make the angle of the subclass accessible.
	virtual float getAngle() = 0;
	// Overwrite this to make the position of the subclass accessible.
	virtual SDL_Point getPosition() = 0;
};

