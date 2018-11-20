#include "cCollisionMgr.h"
#include "cCollider.h"
#include "ICollidable.h"

cCollisionMgr::cCollisionMgr()
{
	
}


cCollisionMgr::~cCollisionMgr()
{
}


void cCollisionMgr::addCollidable(ICollidable * s)
{
	collidables.push_back(s);
}

void cCollisionMgr::calcColl()
{
	// Updating all colliders
	vector<ICollidable*>::iterator cldblA = collidables.begin();
	for (cldblA; cldblA != collidables.end(); ++cldblA)
	{
		(*cldblA)->updateCollider();
	}

	// Comparing every collider with every other collider.
	cldblA = collidables.begin();
	for (cldblA; cldblA != collidables.end(); ++cldblA)
	{
		// Starting sprB from the end and counting down until reaching sprA.
		// This way every combination is only checked once.
		vector<ICollidable*>::iterator cldblB = collidables.end();
		cldblB--;
		while (cldblA != cldblB)
		{
			cCollider* collA = (*cldblA)->getCollider();
			cCollider* collB = (*cldblB)->getCollider();
			// Only checks if both sprites have a collider attached.
			// Sprites without a collider are ignored in collision detection.
			if (collA && collB)
			{
				// Checking for collision. First broad.
				if (checkRadColl(*cldblA,*cldblB))
				{				

					// If they collide, inform both.
					fpoint impA = (*cldblA)->getImpulse();
					fpoint impB = (*cldblB)->getImpulse();
					(*cldblA)->onCollision(impB);
					(*cldblB)->onCollision(impA);
					// Then narrow.
					if (checkNarrowColl(collA, collB))
					{
						// TODO how does the collision information flow?
						// should it be going right to the sprite?

						// If they collide, inform both.
						//collA->onCollision(collB);
						//collB->onCollision(collA);
					}
				}
			}

			cldblB--;
		}
	}
}


bool cCollisionMgr::checkRadColl(ICollidable * a, ICollidable * b)
{
	SDL_Point aCenter = a->getCenter();
	SDL_Point bCenter = b->getCenter();

	// Calculating distance between objects
	int distX = aCenter.x - bCenter.x;
	int distY = aCenter.y - bCenter.y;
	float dist = sqrt(distX*distX + distY*distY);

	// Return whether the added radius of both objects is bigger than the distance.
	return dist < a->getRadius() + b->getRadius();
}

bool cCollisionMgr::checkNarrowColl(cCollider * a, cCollider * b)
{
	/*
	cout << "checkNarrowColl\n";
	// To check the narrow collision we first need to rotate the colliders.
	a->rotate(a->getAngle());
	b->rotate(b->getAngle());
	*/
	//TODO implement narrow collision
	return true;
}
