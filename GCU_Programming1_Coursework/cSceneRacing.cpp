#include "cSceneRacing.h"
#include "gameHeaders.h"
#include "inputHeaders.h"
#include "cPlayer.h"
#include "cCar.h"


cSceneRacing::cSceneRacing(cTextureMgr* theTextureMgr) : cScene()
{

	Input::RegisterDevice(KEYBOARD_ARROWS, 0);	//tmp here, should be on the registration screen
	Input::RegisterDevice(KEYBOARD_WASD, 1);	//tmp here, should be on the registration screen



	// TODO do all the stuff that needs to be done only once when the scene is loaded
	// loading textures
	theTextureMgr->addTexture("street", "Images\\street_tile_map.png");
	theTextureMgr->addTexture("car_01", "Images\\car_01.png");

	// loading sounds


	// Creating sprites
	
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
	
	cCar* testCar = new cCar(1.0f, 0.3f, 5000.0f, 1.0f, 10.0f);
	testCar->setTexture(theTextureMgr->getTexture("car_01"));
	testCar->setSpriteScale({ 1.0, 1.0 });
	testCar->setSheetGrid(1, 1);
	testCar->setSpeed(1);
	testCar->trim(0, 1);
	testCar->play();
	sprites.push_back(testCar);
	

	// Creating players and cameras.
	
	int numberOfPlayers = Input::GetNumberOfPlayers();
	for (int i = 0; i < numberOfPlayers; ++i)
	{
		cPlayer* player = new cPlayer();
		players.push_back(player);
		// Creating a camera per player.
		cCamera* newCam = new cCamera();
		cameras.push_back(newCam);

		// Defining a viewport for the camera.
		// The window gets first split horizontally,
		// if more than 2 players play it also gets split vertically.
		SDL_Rect viewport = newCam->GetViewport();
		if (numberOfPlayers > 1)
		{
			// Setting the width of the viewport to half the window.
			viewport.w = WINDOW_WIDTH / 2;
			// Setting to left or right side, depending on i.
			viewport.x = (WINDOW_WIDTH / 2)*(i % 2);

			if (numberOfPlayers > 2)
			{
				// Setting the height of the viewport to half the window.
				viewport.h = WINDOW_HEIGHT / 2;
				// Setting to up or down side, depending on i.
				viewport.y = (WINDOW_HEIGHT / 2)*(i / 2);
			}
		}
		newCam->SetViewport(viewport);

		// Giving the player a sprite to control.
		player->car = testCar;
	}



}

cSceneRacing::~cSceneRacing()
{
	// Cleaning up textures and sounds loaded for this scene.
	cTextureMgr::getInstance()->deleteTexture("street");

	// Cleaning up the players and cameras.
	vector<cPlayer*>::iterator player = players.begin();
	while (player != players.end())
	{
		// Deleting the controller.
		delete *player;
		// Removing the controller pointer from the vector.
		players.erase(player);

		++player;
	}
}



void cSceneRacing::activate()
{
	// Registering controllers to channels,
	// so that the scene reacts to user input.
	vector<cPlayer*>::iterator player = players.begin();
	int channelIndex = 0;
	for (player; player != players.end(); ++player, ++channelIndex)
	{
		Input::RegisterChannelListener(*player, channelIndex);
	}	

	cSoundMgr::getInstance()->getSnd("who")->play(1);
	cSoundMgr::getInstance()->getSnd("shot")->play(1);

}

void cSceneRacing::deactivate()
{
	// Unregistering player from channels,
	// so that the scene doesn't react to user input anymore.
	vector<cPlayer*>::iterator player = players.begin();
	for (player; player != players.end(); ++player)
	{	
		Input::UnRegisterChannelListener(*player);
	}
}

