#include "cSceneRacing.h"
#include "gameHeaders.h"
#include "inputHeaders.h"
#include "cPlayer.h"
#include "cCar.h"
#include "cCollisionMgr.h"
#include "cGame.h"

cSceneRacing::cSceneRacing(SDL_Renderer* theRenderer) : cScene(theRenderer)
{
	// Setting the timer.
	timer = 0;
	
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
	tmpSpriteMap->setSpriteScale({ 16, 16 });
	tmpSpriteMap->setSheetGrid(4, 4);
	tmpSpriteMap->loadMap("map");
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

	cSprite* safeHouse = new cSprite();
	safeHouse->setTexture(cTextureMgr::getInstance()->getTexture("Charactervector"));
	safeHouse->setSpritePos({ 256 * 14 , 256 * 11 });
	//safeHouse->setSpriteDimensions(256, 256);
	safeHouse->setSpriteScale({ 0.3f, 0.3f });
	sprites.push_back(safeHouse);
	safeHouse->setCollisionMessage(CHECKPOINT);
	safeHouse->setStatic(true);
	theCollisionMgr->addCollider(safeHouse);

	cCar* testCar;
	LPCSTR names[2] = { "car_01_destr" ,"car_02" };

	LPCSTR scoreTextTextureNames[2] = { "scoreTxtr_01" ,"scoreTxtr_02" };

	// Creating players and cameras.	
	int numberOfPlayers = Input::GetNumberOfPlayers();
	for (int i = 0; i < numberOfPlayers; ++i)
	{
		// Creating a player
		cPlayer* player = new cPlayer("Player_" + to_string(i), this);
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
		testCar = new cCar(1.0f, 0.5f, 300.0f, 10.0f, 10.0f);
		testCar->setTexture(cTextureMgr::getInstance()->getTexture(names[i]));
		testCar->setSpritePos( {256 * 14 + 56 + 128 *i , 256 * 10 });// {256 * 4 + 56 + 128 *i , 256 * 7 });
		testCar->setSpriteRotAngle(-180);
		testCar->setSheetGrid(10, 1);
		testCar->setSpriteScale({ 0.5f, 0.5f });
		sprites.push_back(testCar);
		theCollisionMgr->addCollider(testCar);

		// Giving the camera to the collision manager
		theCollisionMgr->addCamera(newCam);

		// Pinning the camera to a sprite.
		newCam->setTarget(testCar);

		// Giving the player a sprite to control.
		player->car = testCar;
		testCar->setController(player);
		
		// Adding score text
		cSpriteText* scoreText = new cSpriteText(theRenderer, cFontMgr::getInstance()->getFont("main_font"), "policeScore");
		scoreText->setSpriteDimensions(100, 100);
		scoreText->setText("0");
		scoreText->setSpritePos({ 0, 50 });
		scoreTexts.push_back(scoreText);
		viewport_UI_sprites[newCam].push_back(scoreText);
		
	}

	// Adding camera for UI for all players
	global_UI_cam.SetViewport({ 0,0,WINDOW_WIDTH,WINDOW_HEIGHT });
	

	// Adding timer text sprites
	for (int p = 0; p < 4; ++p)
	{
		for (int i = 0; i < 10; ++i)
		{
			timerNumbers[p][i] = new cSpriteText(theRenderer, cFontMgr::getInstance()->getFont("main_font"), "timerNumbers_" + (p * 10 + i));
			timerNumbers[p][i]->setSpriteDimensions(50, 50);
			timerNumbers[p][i]->setText(i,"");
			timerNumbers[p][i]->setSpritePos({ WINDOW_WIDTH/2 - p*50, 0 });
			timerNumbers[p][i]->setVisible(false);
			global_UI_sprites.push_back(timerNumbers[p][i]);
		}
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
		++player;
	}
	players.clear();
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
	cSoundMgr::getInstance()->getSnd("racing_music")->play(1);

	// Clearing the scores from the last race.
	cScoreMgr::getInstance()->clear();
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


	// Updating the timer and transition to result scene.
	timer += deltaTime;

	// Display timer
	for (int p = 0; p < 4; ++p)
	{
		// Setting all timer sprites invisible.
		for (int i = 0; i < 10; ++i)
		{
			timerNumbers[p][i]->setVisible(false);
		}
		// Setting the right ones visible.
		int i = ( ((int)timer) / ((int)pow(10,p))) % 10;

		timerNumbers[p][i]->setVisible(true);
	}

		
}

void cSceneRacing::render(SDL_Renderer * renderer)
{
	cScene::render(renderer);
}

void cSceneRacing::playerFinished(cPlayer * p)
{
	// Store the time needed to reach the finish
	cScoreMgr::getInstance()->setScore(p->getName(), timer);

	// Save highscores
	cScoreMgr::getInstance()->SaveScores();

	// Transition to result scene.
	cGame::getInstance()->setActiveScene("result");
}

