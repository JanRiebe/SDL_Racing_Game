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
	vector<cSprite*> sprites;
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
	void render(SDL_Renderer* theRenderer);
};

