#include "cSceneRacing.h"
#include "gameHeaders.h"
#include "inputHeaders.h"


cSceneRacing::cSceneRacing(cTextureMgr* theTextureMgr) : cScene()
{
	// TODO do all the stuff that needs to be done only once when the scene is loaded
	// creating controllers, but not yet registering
	// creating viewports
	// loading textures
	// creating sprites
	// loading sounds

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


cSceneRacing::~cSceneRacing()
{
	//TODO free up the controllers and sprites (also texutes and sounds?) used
}

void cSceneRacing::activate()
{
	//TODO do all the stuff that needs to be done every time the scene gets activated.
	//registering controllers to channels

	//TODO create the relevant amount of controllers, viewports and cameras
	//one for each player.
	//Get the number of players from the input manager.
	
	Input::RegisterDevice(KEYBOARD_ARROWS, 0);	//tmp here, should be on the registration screen

	// Creating a controller and registering to all 4 channels.
	Controller* contr = new Controller(0);
	
	Input::RegisterChannelListener(contr, 0);
	/*
	Input::RegisterChannelListener(contr, 1);
	Input::RegisterChannelListener(contr, 2);
	Input::RegisterChannelListener(contr, 3);
	*/
	controllers.push_back(contr);

	// Creating a viewport for the controller.
	viewports[contr].h = WINDOW_HEIGHT;
	viewports[contr].w = WINDOW_WIDTH;

	// Creating a camera for the controller.
	cameras[contr].SetPosition({ 0,0 });

	
}

void cSceneRacing::deactivate()
{
	//TODO do all the stuff that needs to be done when the scene is deactivated
	//unregistering controllers from channels
}

