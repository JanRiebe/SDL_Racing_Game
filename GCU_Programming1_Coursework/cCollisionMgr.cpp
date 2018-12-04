#include "cCollisionMgr.h"
#include "cCar.h"

cCollisionMgr::cCollisionMgr(SDL_Renderer* r)
{
	theRenderer = r;
	map = NULL;
}


cCollisionMgr::~cCollisionMgr()
{
}

void cCollisionMgr::addCollider(iCollider * c)
{
	allColliders.push_back(c);
}


void cCollisionMgr::addCamera(cCamera * cam)
{
	cameras.push_back(cam);
}



void cCollisionMgr::setMap(cSpriteMap * m)
{
	map = m;
}



void cCollisionMgr::calcColl()
{
	// Organise cars into on screen and off screen cars.
	OrganiseColliders();
	
	// Calculate collisions between colliders.
	// Collisions between on screen colliders.
	DetectCollisions(&onScreenColliders, PIXEL_PERFECT);
	// Collisions between off screen colliders.
	DetectCollisions(&offScreenColliders, BOUNDING_ONLY);
}


void cCollisionMgr::DetectCollisions(vector<iCollider*>* colliders, bool usePixelPerfect)
{
	// Comparing every collider with every other collider.
	vector<iCollider*>::iterator collA = colliders->begin();
	for (collA; collA != colliders->end(); ++collA)
	{


#pragma region Collision with other colliders
		/*
		Collisions between a collider and another collider.
		*/

		// Starting collB from the end and counting down until reaching collA.
		// This way every combination is only checked once.
		vector<iCollider*>::iterator collB = colliders->end();
		collB--;
		while (collA != collB)
		{
			// We can scip static colliders for B because we only want collisions that include at least one dynamic collider.
			// Two static colliders will never collide, since they don't move.
			if ((*collB)->isStatic())
			{
				collB--;
				continue;
			}

			// Declaring and defining variables needed for this collision check.
			usePixelPerfect = usePixelPerfect && (*collA)->usePixelCollision() && (*collB)->usePixelCollision();		// If both colliders have pixel perfect collision activated.
			bool collision = false;					// Whether a collision has occured.
			SDL_Rect overlap;						// The overlapping area between the two bounding boxes in world space.

													// Depending on whether pixel perfect collision shall be performed,
													// broad phase assignes values to overlap or doesn't.
			if (usePixelPerfect)
				// Broad phase collision detection with overlap rect detection.
				collision = checkBBoxColl((*collA)->getBoundingBox(), (*collB)->getBoundingBox(), &overlap);
			else
				// Broad phase collision detection without overlap rect detection.
				collision = checkBBoxColl((*collA)->getBoundingBox(), (*collB)->getBoundingBox());

			// Narrow phase collision detection.
			if (collision && usePixelPerfect)
			{
				collision = checkNarrowColl(*collA, *collB, &overlap);
			}

			// Informing the cars that they have collided.
			if (collision)
			{
				fpoint impulseA = (*collA)->getImpulse();
				fpoint impulseB = (*collB)->getImpulse();
				(*collA)->onCollision((*collB)->getCollisionMessage(), impulseB);
				(*collB)->onCollision((*collA)->getCollisionMessage(), impulseA);

			}

			// Counting down collB until reaching collA.
			collB--;
		}

#pragma endregion



#pragma region Collisions with tiles of the tile map
		/*
		Collisions between a collider an tiles in the map
		*/
		if (map && !(*collA)->isStatic())
		{

			// Going through all tiles in the map
			for (int column = 0; column < MAP_WIDTH; column++)
			{
				for (int row = 0; row < MAP_HEIGHT; row++)
				{
					// Only checking collisions with tiles that are impassable.
					if (map->getMapDefinition().impassable[column][row])
					{
						SDL_Rect* overlap = new SDL_Rect();
						// Broad phase collision detection.
						if (checkBBoxColl((*collA)->getBoundingBox(), map->getBoundingBox(column, row), overlap))
						{
							// Narrow phase collision detection.
							if (checkNarrowColl(*collA, map, overlap))
							{
								// Informing the collider that it has collided.
								(*collA)->onCollision(COLLISION);

							}

						}
						// Freeing up the overlap rectangle
						delete overlap;
						overlap = NULL;
					}
				}
			}
		}

#pragma endregion



	}


}

void cCollisionMgr::OrganiseColliders()
{
	// Clean up the last organisation.
	onScreenColliders.clear();
	offScreenColliders.clear();

	// Going through all colliders to check whether they are on screen.
	vector<iCollider*>::iterator collider = allColliders.begin();
	for (collider; collider != allColliders.end(); ++collider)
	{
		// Checking if the collider is in any split screen viewport.
		SDL_Rect viewport;
		SDL_Point viewPos;		// The position of the collider in viewport coordinates.
		SDL_Rect colliderBBox = (*collider)->getBoundingBox();		// The dimensions of the collider.
		vector<cCamera*>::iterator camera = cameras.begin();
		bool colliderOnScreen = true;
		// While the collider has not been found to be on screen
		// and we haven't reached the last camera.
		while(!colliderOnScreen && camera != cameras.end())
		//for (camera; camera != cameras.end(); ++camera)
		{
			++camera;
			// Getting the coordinates necessary.
			viewport = (*camera)->GetViewport();
			SDL_Rect collBBox_Screen = (*camera)->WorldToScreen(colliderBBox);
			viewPos.x = collBBox_Screen.x;
			viewPos.y = collBBox_Screen.y;

			// Checking if the collider is in the viewport.
			colliderOnScreen =
				// Is the collider within the x dimension of the viewport.
				viewPos.x - colliderBBox.w > 0 && viewPos.x < viewport.w
				&&
				// Is the collider within the y dimension of the viewport.
				viewPos.y - colliderBBox.h > 0 && viewPos.y < viewport.h;
		}
		// Adding the collider to the appropriate vector.
		if(colliderOnScreen)
			onScreenColliders.push_back(*collider);
		else
			offScreenColliders.push_back(*collider);
	}

}



bool cCollisionMgr::checkBBoxColl(SDL_Rect a, SDL_Rect b, SDL_Rect * outOverlap)
{
	// Assigning more readable variables for the sides of the bounding boxes.
	int aLeft = a.x;
	int aRight = a.x + a.w;
	int aUp = a.y;
	int aDown = a.y + a.h;

	int bLeft = b.x;
	int bRight = b.x + b.w;
	int bUp = b.y;
	int bDown = b.y + b.h;

	// With a little help from this page: https://www.geeksforgeeks.org/find-two-rectangles-overlap/
	// No overlap in x
	if (aLeft > bRight || aRight < bLeft)
		return false;
	// No overlap in y
	if (aUp > bDown || aDown < bUp)
		return false;

	// If an overlap rect has been passed in
	// assign it the coordinates of the overlapping region
	// in world coordinates.
	// Using calculation as described here: https://stackoverflow.com/questions/19753134/get-the-points-of-intersection-from-2-rectangles
	if (outOverlap)
	{
		outOverlap->x = max(aLeft, bLeft);
		outOverlap->y = max(aUp, bUp);
		outOverlap->w = min(aRight, bRight) - outOverlap->x;
		outOverlap->h = min(aDown, bDown) - outOverlap->y;
	}

	// There has been a collision of the bounding boxes.
	return true;
}



bool cCollisionMgr::checkNarrowColl(iCollider * a, iCollider * b, SDL_Rect* overlapRect)
{
	// Resturn value
	bool isCollision = false;

	// Storing the old render target in order to reset it afterwards
	SDL_Texture* oldTarget = SDL_GetRenderTarget(theRenderer);


	// Creating a camera for rendering the sprites on the target texture instead of the world position.
	cCamera camera;
	
	// Setting the camera position to the top left of the collsion overlap rect.
		// I want to create a surface that has just the size of the overlap.
		// For this I need to place the top left corner of the overlap in the top left of the target texture.
		// The size of the overlap rect can then be used to determine how much of the target texture needs to be read out in pixels.
	SDL_Point cameraPos;
	cameraPos.x = overlapRect->x;
	cameraPos.y = overlapRect->y;
	camera.SetPosition(cameraPos);

	
	// Reading the data into the surface.
	// From the render target, that is as big as the window,
	// we only read the overlap region.
	SDL_Surface* surfaceA = CreateOverlapSurface(overlapRect, a, &camera);
	SDL_Surface* surfaceB = CreateOverlapSurface(overlapRect, b, &camera);
	
	// Checking through all the pixels in both surfaces.
	// If there is a pixel in which both have an alpha value different than 0,
	// it is considered a collision.
	for (int x = 0; x < overlapRect->w; x++)
	{
		for (int y = 0; y < overlapRect->h; y++) {
			// If this pixel has an alpha != 0 in both surfaces, it is a collision.
			if (get_pixelAlpha(surfaceA, x, y) != 0 && get_pixelAlpha(surfaceB, x, y) != 0)
			{
				isCollision = true;
			}
		}
	}
	
	// Cleaning surfaces.
	SDL_FreeSurface(surfaceA);
	SDL_FreeSurface(surfaceB);

	// Resetting the render target.
	SDL_SetRenderTarget(theRenderer, oldTarget);
		
	return isCollision;
}


// adapted from http://lazyfoo.net/SDL_tutorials/lesson31/index.php
Uint32 cCollisionMgr::get_pixelAlpha(SDL_Surface *surface, int x, int y)
{
	//Convert the pixels to 32 bit 
	Uint32 *pixels = (Uint32 *)surface->pixels; 
	//Get the requested pixel
	Uint32 pix = pixels[ ( y * surface->w ) + x ]; 
	// Get the alpha from the pixel
	// As described here https://stackoverflow.com/questions/12304273/retrieve-last-6-bits-from-an-integer
	return pix & ((1 << 8) - 1);
}


SDL_Surface* cCollisionMgr::CreateOverlapSurface(SDL_Rect* overlapRect, iCollider* sprite, cCamera* camera)
{
	// Creating a render target texture with the size of the overlap rect.
	renderTarget = SDL_CreateTexture(theRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, overlapRect->w, overlapRect->h);
	SDL_SetTextureBlendMode(renderTarget, SDL_BLENDMODE_BLEND);

	// Rendering to render target.
	// Setting the render target.
	SDL_SetRenderTarget(theRenderer, renderTarget);
	// Switching the rendermode of the sprite to to collision
	sprite->setRenderCollision(true);
	// Rendering the texture onto the new render target
	sprite->render(theRenderer, camera);
	// Switching the rendermode of the sprite back to to visual
	sprite->setRenderCollision(false);

	// Creating a surface from the render target texture, in order to read the data.
	// The surface has the size of the overlap rect that needs to be checked.
	SDL_Surface* surface = SDL_CreateRGBSurface(0, overlapRect->w, overlapRect->h, 32, 0, 0, 0, 0);

	// Reading the pixel data into the surface.
	SDL_RenderReadPixels(theRenderer, NULL, surface->format->format, surface->pixels, surface->pitch);

	// Cleaning up render target texture.
	//SDL_DestroyTexture(renderTarget);

	return surface;
}