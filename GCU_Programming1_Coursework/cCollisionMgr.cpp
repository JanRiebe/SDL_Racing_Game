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

void cCollisionMgr::addCar(cCar * car)
{
	allCars.push_back(car);
}

void cCollisionMgr::addSprite(cSprite * sprite)
{
	sprites.push_back(sprite);
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
	OrganiseCars();
	
	// Calculate collisions between cars.
	// Collisions between on screen cars.
	calcCarCollOnScr();
	// Collisions between off screen cars.
	calcCarCollOffScr();

	// Calculate collisions of cars with other sprites.
	calcCarSpriteColl();
	
	// Calculate collisions between cars and tiles.
	if(map)
		calcCarTileColl();
}


void cCollisionMgr::OrganiseCars()
{
	// Clean up the last organisation.
	onScreenCars.clear();
	offScreenCars.clear();

	// Going through all cars to check whether they are on screen.
	vector<cCar*>::iterator car = allCars.begin();
	for (car; car != allCars.end(); ++car)
	{
		// Checking if the car is in any split screen viewport.
		SDL_Rect viewport;
		SDL_Point viewPos;		// The position of the car in viewport coordinates.
		SDL_Rect carDimen = (*car)->getSpriteDimensions();		// The dimensions of the car.
		vector<cCamera*>::iterator camera = cameras.begin();
		bool carOnScreen = true;
		// While the car has not been found to be on screen
		// and we haven't reached the last camera.
		while(!carOnScreen && camera != cameras.end())
		//for (camera; camera != cameras.end(); ++camera)
		{
			++camera;
			// Getting the coordinates necessary.
			viewport = (*camera)->GetViewport();
			viewPos = (*camera)->WorldToScreen((*car)->getPosition());

			// Checking if the car is in the viewport.
			carOnScreen =
				// Is the car within the x dimension of the viewport.
				viewPos.x - carDimen.w > 0 && viewPos.x < viewport.w
				&&
				// Is the car within the y dimension of the viewport.
				viewPos.y - carDimen.h > 0 && viewPos.y < viewport.h;
		}
		// Adding the car to the appropriate vector.
		if(carOnScreen)
			onScreenCars.push_back(*car);
		else
			offScreenCars.push_back(*car);
	}

}



void cCollisionMgr::calcCarCollOnScr()
{
	// Calculating on screen collisions using pixel perfect collision

	// Comparing every car on screen with every other car on screen.
	vector<cCar*>::iterator carA = onScreenCars.begin();
	for (carA; carA != onScreenCars.end(); ++carA)
	{
		// Starting sprB from the end and counting down until reaching sprA.
		// This way every combination is only checked once.
		vector<cCar*>::iterator carB = onScreenCars.end();
		carB--;
		while (carA != carB)
		{
			SDL_Rect* overlap = new SDL_Rect();
			// Broad phase collision detection.
			if (checkBBoxColl((*carA)->getBoundingBox(), (*carB)->getBoundingBox(), overlap))
			{				
				// Narrow phase collision detection.
				if (checkNarrowColl(*carA, *carB, overlap))
				{	
					// Informing the cars that they have collided.
					fpoint impulseA = (*carA)->getImpulse();
					fpoint impulseB = (*carB)->getImpulse();
					(*carA)->onCollision(impulseB);
					(*carB)->onCollision(impulseA);
					
				}
				
			}
			// Freeing up the overlap rectangle
			delete overlap;
			overlap = NULL;

			// Counting down carB until reaching carA.
			carB--;
		}

	}


}

void cCollisionMgr::calcCarCollOffScr()
{
	// Calculating off screen collisions between cars using distance based circle collision.

	// Comparing every car off screen with every other car off screen.
	vector<cCar*>::iterator carA = offScreenCars.begin();
	for (carA; carA != offScreenCars.end(); ++carA)
	{
		// Starting sprB from the end and counting down until reaching sprA.
		// This way every combination is only checked once.
		vector<cCar*>::iterator carB = offScreenCars.end();
		carB--;
		while (carA != carB)
		{
			// Broad phase collision detection only for off screen cars.
			if (checkBBoxColl((*carA)->getBoundingBox(), (*carB)->getBoundingBox(), NULL))
			{
				// Informing the cars that they have collided.
				fpoint impulseA = (*carA)->getImpulse();
				fpoint impulseB = (*carB)->getImpulse();
				(*carA)->onCollision(impulseB);
				(*carB)->onCollision(impulseA);
			}

			// Counting down carB until reaching carA.
			carB--;
		}
	}

}

void cCollisionMgr::calcCarSpriteColl()
{
	//TODO collisions between cars and other sprites
}

void cCollisionMgr::calcCarTileColl()
{
	// Calculating on screen collisions using pixel perfect collision

	// Comparing every car on screen with every tile.
	vector<cCar*>::iterator carA = onScreenCars.begin();
	for (carA; carA != onScreenCars.end(); ++carA)
	{
		for (int column = 0; column < MAP_WIDTH; column++)
		{
			for (int row = 0; row < MAP_HEIGHT; row++)
			{
				// Only checking collisions with tiles that are impassable.
				if (map->getMapDefinition().impassable[column][row])
				{
					SDL_Rect* overlap = new SDL_Rect();
					// Broad phase collision detection.
					if (checkBBoxColl((*carA)->getBoundingBox(), map->getBoundingBox(column, row), overlap))
					{
						// Narrow phase collision detection.
						if (checkNarrowColl(*carA, map, overlap))
						{
							// Informing the cars that they have collided,
							// passing it its own impulse inverted.
							fpoint impulse = (*carA)->getImpulse() * -1;
							(*carA)->onCollision(impulse);

						}

					}
					// Freeing up the overlap rectangle
					delete overlap;
					overlap = NULL;
				}
			}
		}
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



bool cCollisionMgr::checkNarrowColl(cSprite * a, cSprite * b, SDL_Rect* overlapRect)
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


SDL_Surface* cCollisionMgr::CreateOverlapSurface(SDL_Rect* overlapRect, cSprite* sprite, cCamera* camera)
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