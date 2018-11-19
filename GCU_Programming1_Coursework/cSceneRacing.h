#pragma once
#include "cScene.h"
#include "GameConstants.h"
#include "cCamera.h"
#include "cTextureMgr.h"

class cPlayer;

class cSceneRacing :
	public cScene
{
private:
	vector<cPlayer*> players;

public:
	cSceneRacing(cTextureMgr* theTextureMgr);
	~cSceneRacing();
	// Gets called when the scene is activated.
	void activate();
	// Gets called when the scene is deactivated.
	void deactivate();
};

