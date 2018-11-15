#include "cSceneRacing.h"
#include "gameHeaders.h"
#include "inputHeaders.h"


cSceneRacing::cSceneRacing()
{
}


cSceneRacing::~cSceneRacing()
{
}

void cSceneRacing::initialise(cTextureMgr* theTextureMgr)
{
	//TODO create the relevant amount of controllers, viewports and cameras
	//one for each player.
	//Get the number of players from the input manager.
	
	Input::RegisterDevice(KEYBOARD_ARROWS, 0);

	// Creating a controller and registering to all 4 channels.
	Controller* contr = new Controller(0);
	Input::RegisterChannelListener(contr, 0);
	Input::RegisterChannelListener(contr, 1);
	Input::RegisterChannelListener(contr, 2);
	Input::RegisterChannelListener(contr, 3);
	controllers.push_back(contr);

	// Creating a viewport for the controller.
	viewports[contr].h = WINDOW_HEIGHT;
	viewports[contr].w = WINDOW_WIDTH;

	// Creating a camera for the controller.
	cameras[contr].SetPosition({ 0,0 });

	//TODO load all the sprites


	cSpriteMap* tmpSpriteMap = new cSpriteMap();
	tmpSpriteMap->setSpritePos({ 100,0 });
	tmpSpriteMap->setTexture(theTextureMgr->getTexture("Charactervector"));
	tmpSpriteMap->setSpriteScale({ 0.3f, 1.0f });
	tmpSpriteMap->loadMap("foo");
	tmpSpriteMap->setSheetGrid(4, 4);
	sprites.push_back(tmpSpriteMap);

	cSpriteAnimation* tmpSpriteAnim = new cSpriteAnimation();
	tmpSpriteAnim->setTexture(theTextureMgr->getTexture("Charactervector"));
	tmpSpriteAnim->setSpriteScale({ 0.1f, 0.1f });
	tmpSpriteAnim->setSheetGrid(4, 4);
	tmpSpriteAnim->setSpeed(4.0);
	tmpSpriteAnim->trim(4, 4);
	tmpSpriteAnim->play();
	sprites.push_back(tmpSpriteAnim);
}

