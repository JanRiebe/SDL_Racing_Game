#include "cSceneRacing.h"
#include "gameHeaders.h"
#include "inputHeaders.h"
#include "cPlayer.h"
#include "cCar.h"
#include "cCollisionMgr.h"


//TODO remove test callback function
void testfuntionA()
{
	cout << "function A evoked\n";
}
void testfuntionB()
{
	cout << "function B evoked\n";
}

cSceneRacing::cSceneRacing(SDL_Renderer* theRenderer) : cScene()
{

	Input::RegisterDevice(KEYBOARD_ARROWS, 0);	//tmp here, should be on the registration screen
	Input::RegisterDevice(KEYBOARD_WASD, 1);	//tmp here, should be on the registration screen

	// Creating collsion manager
	theCollisionMgr = new cCollisionMgr(theRenderer);


	// loading textures
	cTextureMgr::getInstance()->addTexture("street", "Images\\street_tile_map.png");
	cTextureMgr::getInstance()->addTexture("street_coll", "Images\\street_tile_map_collision.png");
	cTextureMgr::getInstance()->addTexture("car_01", "Images\\car_01.png");
	cTextureMgr::getInstance()->addTexture("car_01_destr", "Images\\car_01_destr.png");
	cTextureMgr::getInstance()->addTexture("car_02", "Images\\ramp.png");

	// loading sounds


	// Creating sprites
	
	cSpriteMap* tmpSpriteMap = new cSpriteMap();
	tmpSpriteMap->setSpritePos({ 0,0 });
	tmpSpriteMap->setTexture(cTextureMgr::getInstance()->getTexture("street"));
	tmpSpriteMap->setCollisionTexture(cTextureMgr::getInstance()->getTexture("street_coll"));
	tmpSpriteMap->setSpriteScale({ 50, 50 });
	tmpSpriteMap->setSheetGrid(4, 4);
	tmpSpriteMap->loadMap("foo");
	sprites.push_back(tmpSpriteMap);
	theCollisionMgr->setMap(tmpSpriteMap);
	/*
	cSpriteAnimation* tmpSpriteAnim = new cSpriteAnimation();
	tmpSpriteAnim->setTexture(cTextureMgr::getInstance()->getTexture("Charactervector"));
	tmpSpriteAnim->setSpriteScale({ 0.1f, 0.1f });
	tmpSpriteAnim->setSheetGrid(4, 4);
	tmpSpriteAnim->setSpeed(4.0);
	tmpSpriteAnim->trim(4, 4);
	tmpSpriteAnim->play();
	sprites.push_back(tmpSpriteAnim);
	*/
	cCar* testCar;
	LPCSTR names[2] = { "car_01_destr" ,"car_02" };

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

		// Assigning values to the car
		testCar = new cCar(1.0f, 0.1f, 500.0f, 10.0f, 5.0f);
		testCar->setTexture(cTextureMgr::getInstance()->getTexture(names[i]));
		testCar->setSpritePos({ 0, 200*i });
		testCar->setSpriteRotAngle(180 * i);
		testCar->setSheetGrid(10, 1);
		testCar->setSpriteScale({ 0.5f, 0.5f });
		sprites.push_back(testCar);
		theCollisionMgr->addCar(testCar);

		// Giving the camera to the collision manager
		theCollisionMgr->addCamera(newCam);
		
		// Pinning the camera to a sprite.
		newCam->setTarget(testCar);

		// Giving the player a sprite to control.
		player->car = testCar;
		testCar->setController(player);

		/*
		// Adding test text sprite
		cSpriteText* testText = new cSpriteText(theRenderer, cFontMgr::getInstance()->getFont("pirate"), "scoreText");
		testText->setText("Score");
		testText->setSpriteDimensions(newCam->GetViewport().w, newCam->GetViewport().h / 10);
		testText->setSpritePos({ 50, 50 });
		uiSprites[newCam].push_back(testText);
		player->setScoreSprite(testText);
				*/
	}


}

cSceneRacing::~cSceneRacing()
{
	// Deactivate the scene, to ensure no controllers are registered to input channels anymore.
	deactivate();

	// Cleaning up collision manager
	delete theCollisionMgr;

	// Cleaning up textures and sounds loaded for this scene.
	cTextureMgr::getInstance()->deleteTexture("street");
	cTextureMgr::getInstance()->deleteTexture("car_01");
	cTextureMgr::getInstance()->deleteTexture("car_01_destr");
	cTextureMgr::getInstance()->deleteTexture("car_02");

	// Cleaning up the players.
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
		// Registering player controller
		Input::RegisterChannelListener(*player, channelIndex);

	}	
	
	// Playing background sounds
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

void cSceneRacing::update(double deltaTime)
{
	// Letting scene update prites and cameras and stuff.
	cScene::update(deltaTime);

	// Calculating collisions
	theCollisionMgr->calcColl();
}

void cSceneRacing::render(SDL_Renderer * renderer)
{
	cScene::render(renderer);
}

