#pragma once
#include "cScene.h"
#include "GameConstants.h"
#include "cCamera.h"
#include "cTextureMgr.h"


class cSceneRacing :
	public cScene
{
public:
	cSceneRacing(cTextureMgr* theTextureMgr);
	// Gets called when the scene is activated.
	void activate();
	// Gets called when the scene is deactivated.
	void deactivate();
};

