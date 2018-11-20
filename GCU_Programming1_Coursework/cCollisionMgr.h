#pragma once

#include "gameHeaders.h"

class ICollidable;

class cCollisionMgr
{
private:
	vector<ICollidable*> collidables;
	// Checks whether the radius of two colliders overlap.
	bool checkRadColl(ICollidable* a, ICollidable* b);
	// Check whether tow colliders overlap narrowly.
	bool checkNarrowColl(cCollider* a, cCollider* b);
public:
	cCollisionMgr();
	~cCollisionMgr();
	void addCollidable(ICollidable* collider);
	// Calculates collisions and informs colliders.
	void calcColl();
};

