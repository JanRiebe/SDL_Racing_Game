#pragma once
#include "cScene.h"
#include "GameConstants.h"

class cCollisionMgr;
class cPlayer;
class cSpriteText;

class cSceneRacing :
	public cScene
{
private:
	vector<cPlayer*> players;
	cCollisionMgr* theCollisionMgr;
	double timer;
	cSpriteText* timerText;
	cSpriteText* scoreTexts[NUMBER_OF_TEAMS];

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

