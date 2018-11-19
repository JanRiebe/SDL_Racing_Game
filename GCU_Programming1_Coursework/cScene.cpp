#include "cScene.h"
#include "gameHeaders.h"
#include "inputHeaders.h"


cScene::cScene()
{
	isInitialised = false;
}


cScene::~cScene()
{
	

	// Cleaning up the sprites.
	vector<cSprite*>::iterator sprite = sprites.begin();
	while (sprite != sprites.end())
	{
		// Deleting the sprite.
		delete *sprite;
		// Removing the sprite from the vector.
		sprites.erase(sprite);

		++sprite;
	}

	// Cleaning up the cameras.
	vector<cCamera*>::iterator camera = cameras.begin();
	while (camera != cameras.end())
	{
		// Deleting the camera.
		delete *camera;
		// Removing the camera from the vector.
		cameras.erase(camera);

		++camera;
	}

}



void cScene::update(double deltaTime)
{
	
	// Updating all sprites
	vector<cSprite*>::iterator it = sprites.begin();
	for (it; it != sprites.end(); ++it) {
		(*it)->update(deltaTime);
	}
	
	// Updating all cameras
	vector<cCamera*>::iterator camera = cameras.begin();
	for (camera; camera != cameras.end(); ++camera)
	{
		(*camera)->update(deltaTime);
	}
}

void cScene::render(SDL_Renderer * theRenderer)
{
	
	int i = 0;
	// Rendering one viewport for every player
	vector<cCamera*>::iterator camera = cameras.begin();
	for (camera; camera != cameras.end(); ++camera)
	{
		// Setting the right viewport for the player
		SDL_RenderSetViewport(theRenderer, &(*camera)->GetViewport());
		
		// Rendering all sprites one by one
		vector<cSprite*>::iterator it = sprites.begin();
		for (it; it != sprites.end(); ++it) {
			// Rendering the sprite using the camera for the relevant player
			(*it)->render(theRenderer, *camera);
		}
		
	}
	
}