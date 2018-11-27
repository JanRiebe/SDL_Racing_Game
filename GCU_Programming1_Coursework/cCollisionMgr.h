#pragma once

#include "gameHeaders.h"

class cCar;
class cCamera;

class cCollisionMgr
{
private:
	// Reference to the renderer used for pixel perfect collision.
	SDL_Renderer* theRenderer;
	// Texture used as render target in pixel perfect collision detection.
	//SDL_Texture* renderTarget;
	// Pointers to all cameras in the scene. Used to determine whether a car is on screen or off screen.
	vector<cCamera*> cameras;
	// All pixel perfect collision is a car colliding with something else.
	vector<cCar*> allCars;
	vector<cCar*> onScreenCars;
	vector<cCar*> offScreenCars;
	// Sprites that the cars can collide with.
	vector<cSprite*> sprites;
	// Map definition for collision with tiles.
	cSpriteMap* map;


	// Splits the cars into on screen and off screen cars.
	void OrganiseCars();
	// Calculates collisions between cars.
	void calcCarCollOnScr();
	void calcCarCollOffScr();
	// Calculates collisions between cars and other sprites.
	void calcCarSpriteColl();
	// Calculates collisions between cars and tiles from the map definition.
	void calcCarTileColl();
	// Checks whether the bounding boxes of two colliders overlap. outOverlap will be set to the rect representing the overlap of the two cars in world coordinates. If there is no overlap outOverlap is not changed. outOverlap will be ignored if it is NULL
	//bool checkBBoxColl(cSprite* a, cSprite* b, SDL_Rect* outOverlap);
	bool checkBBoxColl(SDL_Rect a, SDL_Rect b, SDL_Rect* outOverlap);
	// Check whether tow colliders overlap narrowly.
	bool cCollisionMgr::checkNarrowColl(cSprite * a, cSprite * b, SDL_Rect* overlapRect);
	// Create a surface that contains the pixels of a colliding sprite that overlap with another sprite during a collision. The overlap rect should be in world coordinates.
	SDL_Surface* CreateOverlapSurface(SDL_Rect* overlapRect, cSprite* sprite, cCamera* theCamera);
	Uint32 get_pixelAlpha(SDL_Surface *surface, int x, int y);
public:
	cCollisionMgr(SDL_Renderer* r);
	~cCollisionMgr();
	void addCar(cCar* car);
	void addSprite(cSprite* sprite);
	void addCamera(cCamera* cam);
	void setMap(cSpriteMap* m);
	// Calculates collisions and informs colliders.
	void calcColl();


	SDL_Texture* renderTarget;
};

