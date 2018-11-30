#pragma once
#include "cScene.h"
#include "GameConstants.h"

class cButtonController;
class cSpriteText;

class cSceneHighscores :
	public cScene
{
public:
	cSceneHighscores(SDL_Renderer* theRenderer);
	~cSceneHighscores();

	// Gets called when the scene is activated.
	void activate();
	// Gets called when the scene is deactivated.
	void deactivate();

private:
	cButtonController* buttonContr;
	cSpriteText* highscoreTexts[HIGHSCORE_LIST_ENTRIES];
};

