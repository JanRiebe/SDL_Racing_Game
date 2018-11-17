#include "cSceneRacing.h"
#include "gameHeaders.h"
#include "inputHeaders.h"


cSceneRacing::cSceneRacing(cTextureMgr* theTextureMgr) : cScene()
{
	// TODO do all the stuff that needs to be done only once when the scene is loaded
	// loading textures
	// creating sprites
	theTextureMgr->addTexture("street", "Images\\street_tile_map.png");

	// loading sounds

	Input::RegisterDevice(KEYBOARD_ARROWS, 0);	//tmp here, should be on the registration screen
	Input::RegisterDevice(KEYBOARD_WASD, 1);	//tmp here, should be on the registration screen


	// Creating a controllers for all players.
	int numberOfPlayers = Input::GetNumberOfPlayers();
	for (int i = 0; i < numberOfPlayers; ++i)
	{
		Controller* contr = new Controller(i);
		controllers.push_back(contr);

		// Defining a viewport for the controller.
		// The window gets first split horizontally,
		// if more than 2 players play it also gets split vertically.
		if (numberOfPlayers > 1)
		{
			// Setting the width of the viewport to half the window.
			viewports[contr].w = WINDOW_WIDTH / 2;
			// Setting to left or right side, depending on i.
			viewports[contr].x = (WINDOW_WIDTH / 2)*(i % 2);

			if (numberOfPlayers > 2)
			{
				// Setting the height of the viewport to half the window.
				viewports[contr].h = WINDOW_HEIGHT / 2;
				// Setting to up or down side, depending on i.
				viewports[contr].y = (WINDOW_HEIGHT / 2)*(i / 2);
			}
			else
				// If no more than two players set height to full window.
				viewports[contr].h = WINDOW_HEIGHT;
		}
		else
		{
			// If only one player set width and height to full window.
			viewports[contr].w = WINDOW_WIDTH;
			viewports[contr].h = WINDOW_HEIGHT;
		}

		// Creating a camera for the controller.
		cameras[contr] = new cCamera();
	}


	//TODO load all the sprites


	cSpriteMap* tmpSpriteMap = new cSpriteMap();
	tmpSpriteMap->setSpritePos({ -100,-100 });
	tmpSpriteMap->setTexture(theTextureMgr->getTexture("street"));
	tmpSpriteMap->setSpriteScale({ 1.5f, 1.5f });
	tmpSpriteMap->setSheetGrid(4, 4);
	tmpSpriteMap->loadMap("foo");
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



void cSceneRacing::activate()
{
	// Registering controllers to channels,
	// so that the scene reacts to user input.
	vector<Controller*>::iterator controller = controllers.begin();
	int channelIndex = 0;
	for (controller; controller != controllers.end(); ++controller, ++channelIndex)
	{
		Input::RegisterChannelListener(*controller, channelIndex);
	}	

	cSoundMgr::getInstance()->getSnd("who")->play(1);
	cSoundMgr::getInstance()->getSnd("shot")->play(1);

	// Giving the controller control over in game objects.
	controller = controllers.begin();
	for (controller; controller != controllers.end(); ++controller, ++channelIndex)
	{
		(*controller)->cam = cameras[*controller];
	}
}

void cSceneRacing::deactivate()
{
	// Unregistering controllers to channels,
	// so that the scene doesn't react to user input anymore.
	vector<Controller*>::iterator controller = controllers.begin();
	int channelIndex = 0;
	for (controller; controller != controllers.end(); ++controller, ++channelIndex)
	{	
		Input::UnRegisterChannelListener(*controller);
	}
}

