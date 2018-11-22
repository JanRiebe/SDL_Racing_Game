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

	// Cleaning up the ui sprites.
	sprite = uiSprites.begin();
	while (sprite != uiSprites.end())
	{
		// Deleting the sprite.
		delete *sprite;
		// Removing the sprite from the vector.
		uiSprites.erase(sprite);

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

	// Updating all ui sprites
	it = uiSprites.begin();
	for (it; it != uiSprites.end(); ++it) {
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
		
		// Rendering all world space sprites
		vector<cSprite*>::iterator it = sprites.begin();
		for (it; it != sprites.end(); ++it) {
			// Rendering the sprite using the camera for the relevant player
			(*it)->render(theRenderer, *camera);
		}		

		// Rendering all screen space sprites
		// Saving the camera position so it can be restored.
		SDL_Point tmpCamPos = (*camera)->GetPosition();
		// Setting the camera position to 0,0 to render in screen/viewport space.
		(*camera)->SetPosition({ 0,0 });
		it = uiSprites.begin();
		for (it; it != uiSprites.end(); ++it) {
			// Rendering the sprite using the camera for the relevant player
			(*it)->render(theRenderer, *camera);
		}
		// Resetting the camera position
		(*camera)->SetPosition(tmpCamPos);
	}
	
}