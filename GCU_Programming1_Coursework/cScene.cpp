#include "cScene.h"
#include "gameHeaders.h"
#include "inputHeaders.h"


cScene::cScene()
{
}


cScene::~cScene()
{
	// Cleaning up the controllers.
	vector<Controller*>::iterator controller = controllers.begin();
	while ( controller != controllers.end())
	{
		// Deleting the controller.
		delete *controller;
		// Removing the controller from the vector.
		controllers.erase(controller);

		++controller;
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
			(*it)->render(theRenderer, &cameras[*controller]);
		}
	}
	
}