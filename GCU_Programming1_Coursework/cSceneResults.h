#pragma once
#include "cScene.h"
#include "GameConstants.h"


class cButtonController;
class cSpriteText;

class cSceneResults :
	public cScene
{
private:
	cButtonController* buttonContr;
	//cSpriteText* scoreTexts[NUMBER_OF_TEAMS];

public:
	cSceneResults(SDL_Renderer* theRenderer);
	~cSceneResults();
	// Gets called when the scene is activated.
	void activate();
	// Gets called when the scene is deactivated.
	void deactivate();
};

