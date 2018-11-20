#include "cCollider.h"



cCollider::cCollider()
{
}


cCollider::~cCollider()
{
	// Cleaning up collision primitives.
	vector<SDL_Point* >::iterator point = collisionPoints.begin();
	for (point; point != collisionPoints.end();++point)
	{
		delete *point;
	}
}

void cCollider::rotate(float angle, SDL_Point center)
{
	//TODO rotate the primitives using the homogenous matrix method
}

bool cCollider::checkCollision(cCollider * other)
{
	// TODO check collision
	return false;
}

void cCollider::generateFromSurface(SDL_Surface * s)
{
	//TODO generate collision points by appying edge detection filter
}
