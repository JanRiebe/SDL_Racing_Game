#pragma once
#include "cScene.h"


class cButtonController;

class cSceneResults :
	public cScene
{
private:
	cButtonController* buttonContr;

public:
	cSceneResults(SDL_Renderer* theRenderer);
	~cSceneResults();
	// Gets called when the scene is activated.
	void activate();
	// Gets called when the scene is deactivated.
	void deactivate();
};

