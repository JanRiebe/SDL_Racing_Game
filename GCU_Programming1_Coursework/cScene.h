#pragma once
#include <vector>
#include <map>
#include "SDL.h"

using namespace std;


// Forward declarations
class cSprite;
class cCamera;


class cScene
{
protected:
	vector<cSprite*> sprites;		// Sprites that are rendered in world space
	vector<cSprite*> uiSprites;		// Sprites that are rendered in screen space
	vector<cCamera*> cameras;

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

