#include "cCollisionMgr.h"
#include "cCollider.h"

cCollisionMgr::cCollisionMgr()
{
	
}


cCollisionMgr::~cCollisionMgr()
{
}


void cCollisionMgr::addCollider(cCollider * collider)
{
	colliders.push_back(collider);
}

void cCollisionMgr::calcColl()
{
	// Comparing every collider with every other collider.
	vector<cCollider*>::iterator collA = colliders.begin();
	for (collA; collA != colliders.end(); ++collA)
	{
		// Starting collB from the end and counting down until reaching collA.
		// This way every combination is only checked once.
		vector<cCollider*>::iterator collB = colliders.end();
		collB--;
		while (collA != collB)
		{
			// Checking for collision. First broad.
			if (checkBBoxColl(*collA,*collB))
			{
				// Then narrow.
				if (checkNarrowColl(*collA, *collB))
				{
					// If they collide, inform both.
					(*collA)->onCollision(*collB);
					(*collB)->onCollision(*collA);
				}
			}

			collB--;
		}
	}
}


//TODO maybe in the broad phase I should just check for the sprite transform rect as bounding box.
//It is already assigned and doesn't need to be updated and stuff.
bool cCollisionMgr::checkBBoxColl(cCollider * a, cCollider * b)
{
	int aLeft = a->bBox.x + a->getPosition().x;
	int aRight = a->bBox.x + a->bBox.w + a->getPosition().x;
	int aUp = a->bBox.y + a->getPosition().y;
	int aDown = a->bBox.y + a->bBox.h + a->getPosition().y;

	int bLeft = b->bBox.x + b->getPosition().x;
	int bRight = b->bBox.x + b->bBox.w + b->getPosition().x;
	int bUp = b->bBox.y + b->getPosition().y;
	int bDown = b->bBox.y + b->bBox.h + b->getPosition().y;

	return
		// Overlapp in x dimension
		((aLeft < bLeft && aRight > bLeft)
			||
			(aRight > bRight && aLeft < bRight))
		&&
		// Overlap in y dimension
		((aUp < bUp && aDown > bUp)
			||
			(aDown > bDown && aUp < bDown));
	
}

bool cCollisionMgr::checkNarrowColl(cCollider * a, cCollider * b)
{
	cout << "checkNarrowColl\n";
	// To check the narrow collision we first need to rotate the colliders.
	a->rotate(a->getAngle());
	b->rotate(b->getAngle());

	//TODO implement narrow collision
	return true;
}
