#pragma once
#include "cScene.h"

class cCollisionMgr;
class cPlayer;
class cButtonController;

class cSceneRacing :
	public cScene
{
private:
	vector<cPlayer*> players;
	cCollisionMgr* theCollisionMgr;
	cButtonController* buttonContr;
public:
	cSceneRacing(SDL_Renderer* theRenderer);
	~cSceneRacing();
	// Gets called when the scene is activated.
	void activate();
	// Gets called when the scene is deactivated.
	void deactivate();
	void update(double deltaTime);
	void render(SDL_Renderer* renderer);	//TODO remove
};

