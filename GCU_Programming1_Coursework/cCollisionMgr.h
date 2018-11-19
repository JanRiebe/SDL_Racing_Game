#pragma once

#include "gameHeaders.h"

class cCollider;

class cCollisionMgr
{
private:
	vector<cCollider*> colliders;
	// Checks whether the bounding boxes of two colliders overlap.
	bool checkBBoxColl(cCollider* a, cCollider* b);
	// Check whether tow colliders overlap narrowly.
	bool checkNarrowColl(cCollider* a, cCollider* b);
public:
	cCollisionMgr();
	~cCollisionMgr();
	void addCollider(cCollider* collider);
	// Calculates collisions and informs colliders.
	void calcColl();
};

