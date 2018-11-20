#include "ICollidable.h"

ICollidable::ICollidable()
{
	collider = NULL;
	radius = 0;
}

ICollidable::~ICollidable()
{
	delete collider;
}

void ICollidable::setCollider(cCollider* c)
{
	collider = c;
}

cCollider * ICollidable::getCollider()
{
	return collider;
}
