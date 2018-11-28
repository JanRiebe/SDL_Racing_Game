#pragma once

#include "gameHeaders.h"

class cCar;
class cCamera;

#define BOUNDING_ONLY false
#define PIXEL_PERFECT true


class cCollisionMgr
{
private:
	// Reference to the renderer used for pixel perfect collision.
	SDL_Renderer* theRenderer;
	// Texture used as render target in pixel perfect collision detection.
	SDL_Texture* renderTarget;

	// Pointers to all cameras in the scene. Used to determine whether a collider is on screen or off screen.
	vector<cCamera*> cameras;

	// Colliders
	vector<iCollider*> allColliders;
	vector<iCollider*> onScreenColliders;
	vector<iCollider*> offScreenColliders;
	
	// Map for collision with tiles.
	cSpriteMap* map;


	// Calculates the collisions of all colliders in the vector given as argument.
	void DetectCollisions(vector<iCollider*>* colliders, bool usePixelPerfect);
	
	// Splits the controllers into on screen and off screen controllers.
	void OrganiseColliders();

	// Checks whether the bounding boxes of two colliders overlap. outOverlap will be set to the rect representing the overlap of the two cars in world coordinates. If there is no overlap outOverlap is not changed. outOverlap will be ignored if it is NULL
	bool checkBBoxColl(SDL_Rect a, SDL_Rect b, SDL_Rect* outOverlap = NULL);
	
	// Check whether the non transparent pixels of two colliders overlap.
	bool cCollisionMgr::checkNarrowColl(iCollider * a, iCollider * b, SDL_Rect* overlapRect);
	
	// Create a surface that contains the pixels of a colliding sprite that overlap with another sprite during a collision. The overlap rect should be in world coordinates.
	SDL_Surface* CreateOverlapSurface(SDL_Rect* overlapRect, iCollider* sprite, cCamera* theCamera);
	
	// Read out the alpha value from a pixel.
	Uint32 get_pixelAlpha(SDL_Surface *surface, int x, int y);


public:
	cCollisionMgr(SDL_Renderer* r);
	~cCollisionMgr();

	void addCollider(iCollider* c);
	void addCamera(cCamera* cam);
	void setMap(cSpriteMap* m);

	// Call this to perform collision detection.
	void calcColl();

};

