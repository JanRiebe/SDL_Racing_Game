#pragma once
#include "gameHeaders.h"

class cCollider
{
private:
	// The angle to which the collisionPoints were previously rotated.
	// Used to rotate them relative to the original position.
	float previousRotationAngle;
	// The pixel coordinates of the outline of the collider, relative to the sprite coordinates.
	vector<SDL_Point*> collisionPoints;
public:
	cCollider();
	~cCollider();
	// Rotates all primitives to the given angle.
	void rotate(float angle, SDL_Point center);
	// Tests whether this collider collides with the other.
	bool checkCollision(cCollider* other);
	// Generates collision points at edges in the alpha channel.
	void generateFromSurface(SDL_Surface* s);
};

