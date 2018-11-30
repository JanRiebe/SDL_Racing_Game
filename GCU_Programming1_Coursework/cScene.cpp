#include "cScene.h"
#include "gameHeaders.h"
#include "inputHeaders.h"


cScene::cScene(SDL_Renderer * renderer): theRenderer(renderer)
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
		++sprite;
	}
	sprites.clear();

	

	// Cleaning up the cameras and viewport ui sprites.
	vector<cCamera*>::iterator camera = cameras.begin();
	while (camera != cameras.end())
	{
		// Cleaning up the ui sprites.
		sprite = viewport_UI_sprites[(*camera)].begin();
		while (sprite != viewport_UI_sprites[(*camera)].end())
		{
			// Deleting the sprite.
			delete *sprite;

			++sprite;
		}
		viewport_UI_sprites[(*camera)].clear();

		// Deleting the camera.
		delete *camera;

		++camera;
	}
	cameras.clear();



	// Cleaning up the global ui sprites.
	sprite = global_UI_sprites.begin();
	while (sprite != global_UI_sprites.end())
	{
		// Deleting the sprite.
		delete *sprite;

		++sprite;
	}
	global_UI_sprites.clear();

}



void cScene::update(double deltaTime)
{

	// Updating all sprites
	vector<cSprite*>::iterator it = sprites.begin();
	for (it; it != sprites.end(); ++it) {
		(*it)->update(deltaTime);
	}

	// Updating all cameras and viewport ui sprites
	vector<cCamera*>::iterator camera = cameras.begin();
	for (camera; camera != cameras.end(); ++camera)
	{
		// Updating camera
		(*camera)->update(deltaTime);

		// Updating ui sprites
		it = viewport_UI_sprites[(*camera)].begin();
		for (it; it != viewport_UI_sprites[(*camera)].end(); ++it) {
			(*it)->update(deltaTime);
		}
	}

	// Updating all global UI sprites
	it = global_UI_sprites.begin();
	for (it; it != global_UI_sprites.end(); ++it) {
		(*it)->update(deltaTime);
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

		// Rendering all viewport space sprites
		// Saving the camera position so it can be restored.
		SDL_Point tmpCamPos = (*camera)->GetPosition();
		// Setting the camera position to 0,0 to render in screen/viewport space.
		(*camera)->SetPosition({ 0,0 });
		it = viewport_UI_sprites[(*camera)].begin();
		for (it; it != viewport_UI_sprites[(*camera)].end(); ++it) {
			// Rendering the sprite using the camera for the relevant player
			(*it)->render(theRenderer, *camera);
		}
		// Resetting the camera position
		(*camera)->SetPosition(tmpCamPos);

	}
	
	// Rendering global UI sprites
	// Setting the right viewport for the whole frame
	SDL_RenderSetViewport(theRenderer, &(global_UI_cam.GetViewport()));
	vector<cSprite*>::iterator it = global_UI_sprites.begin();
	for (it; it != global_UI_sprites.end(); ++it) {
		// Rendering the sprite using the global UI camera
		(*it)->render(theRenderer, &global_UI_cam);
	}
}