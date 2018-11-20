#pragma once
#include "cScene.h"
#include "GameConstants.h"
#include "cCamera.h"
#include "cTextureMgr.h"

class cPlayer;
class cCollisionMgr;

class cSceneRacing :
	public cScene
{
private:
	vector<cPlayer*> players;
	cCollisionMgr* theCollisionMgr;
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

