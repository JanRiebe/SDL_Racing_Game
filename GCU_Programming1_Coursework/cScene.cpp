#include "cScene.h"
#include "gameHeaders.h"
#include "inputHeaders.h"


cScene::cScene()
{
	isInitialised = false;
}


cScene::~cScene()
{
	// Cleaning up the controllers and cameras.
	vector<Controller*>::iterator controller = controllers.begin();
	while ( controller != controllers.end())
	{
		// Deleting the camera.
		delete cameras[*controller];
		// Removing the camera pointer from the map.
		cameras.erase(*controller);

		// Deleting the controller.
		delete *controller;
		// Removing the controller pointer from the vector.
		controllers.erase(controller);

		++controller;
	}

	// Cleaning up the sprites.
	vector<cSprite*>::iterator sprite = sprites.begin();
	while (sprite != sprites.end())
	{
		// Deleting the controller.
		delete *sprite;
		// Removing the controller from the vector.
		sprites.erase(sprite);

		++sprite;
	}

}



void cScene::update(double deltaTime)
{
	
	// Updating all sprites
	vector<cSprite*>::iterator it = sprites.begin();
	for (it; it != sprites.end(); ++it) {
		(*it)->update(deltaTime);
	}
	
}

void cScene::render(SDL_Renderer * theRenderer)
{
	// Rendering one viewport for every player
	vector<Controller*>::iterator controller = controllers.begin();
	for (controller; controller != controllers.end(); ++controller)
	{
		// Setting the right viewport for the player
		SDL_RenderSetViewport(theRenderer, &viewports[*controller]);
		// Rendering all sprites one by one
		vector<cSprite*>::iterator it = sprites.begin();
		for (it; it != sprites.end(); ++it) {
			// Rendering the sprite using the camera for the relevant player
			(*it)->render(theRenderer, cameras[*controller]);
		}
	}
	
}