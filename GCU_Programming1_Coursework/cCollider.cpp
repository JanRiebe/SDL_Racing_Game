#include "cCollider.h"



cCollider::cCollider()
{
}


cCollider::~cCollider()
{
	// Cleaning up collision primitives.
	vector<SDL_Rect* >::iterator prim = collisionPrimitives.begin();
	for (prim; prim != collisionPrimitives.end();++prim)
	{
		delete *prim;
	}
}

void cCollider::rotate(float angle)
{
	//TODO rotate the primitives using the homogenous matrix method
}
