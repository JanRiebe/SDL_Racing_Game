#pragma once
#include "cScene.h"

class cButtonController;

class cSceneStart :
	public cScene
{
private:
	cButtonController* buttonContr;

public:
	cSceneStart(SDL_Renderer* theRenderer);
	~cSceneStart();
	// Gets called when the scene is activated.
	void activate();
	// Gets called when the scene is deactivated.
	void deactivate();
};

