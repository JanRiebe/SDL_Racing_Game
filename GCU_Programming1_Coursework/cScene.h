#pragma once
#include <vector>
#include <map>
#include "SDL.h"
#include "cCamera.h"

using namespace std;


// Forward declarations
class cSprite;
class cCamera;


class cScene
{
protected:
	vector<cSprite*> sprites;		// Sprites that are rendered in world space
	map<cCamera*, vector<cSprite*>> viewport_UI_sprites;		// Sprites that are rendered in viewport space, organised by camera
	vector<cSprite*> global_UI_sprites;							// Sprites that are rendered in window space, using the global_UI_cam
	vector<cCamera*> cameras;
	cCamera global_UI_cam;

	bool isInitialised;		// Indicates whether activate has been called at least once.
public:
	cScene();
	virtual ~cScene();
	// Gets called when the scene is activated.
	virtual void activate() = 0;
	// Gets called when the scene is deactivated.
	virtual void deactivate() = 0;
	// Calls update on all sprites in this scene.
	virtual void update(double deltaTime);
	// Calls render on all sprites in this scene.
	virtual void render(SDL_Renderer* theRenderer);
};

