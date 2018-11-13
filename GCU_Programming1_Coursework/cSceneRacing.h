#pragma once
#include "cScene.h"
#include "GameConstants.h"
#include "cCamera.h"
#include "cTextureMgr.h"


class cSceneRacing :
	public cScene
{
public:
	cSceneRacing();
	~cSceneRacing();
	// Gets called when the scene is activated.
	void initialise(cTextureMgr* theTextureMgr);
};

