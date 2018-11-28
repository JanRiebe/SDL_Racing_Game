#include "cSceneStart.h"
#include "GameConstants.h"
#include "gameHeaders.h"
#include "inputHeaders.h"
#include "buttonCallbackFunctions.h"




cSceneStart::cSceneStart(SDL_Renderer* theRenderer)
{
	

	Input::RegisterDevice(KEYBOARD_ARROWS, 0);	//tmp here, should be on the registration screen
	Input::RegisterDevice(KEYBOARD_WASD, 1);	//tmp here, should be on the registration screen

	

	// loading textures
	cTextureMgr::getInstance()->addTexture("Background", "Images\\tmp_menu_bg.jpg");



	// loading sounds



	// Creating camera


	// Creating sprites

	// Background
	cSprite * background = new cSprite();
	background->setTexture(cTextureMgr::getInstance()->getTexture("Background"));
	background->setSpriteDimensions(WINDOW_WIDTH, WINDOW_HEIGHT);
	global_UI_sprites.push_back(background);

	// Adding title text sprite
	cSpriteText* titleText = new cSpriteText(theRenderer, cFontMgr::getInstance()->getFont("pirate"), "titleTxt");
	titleText->setText("Jan's fun and educational racing game");
	titleText->setSpriteDimensions(WINDOW_WIDTH/2, WINDOW_WIDTH / 10);
	titleText->setSpritePos({ WINDOW_WIDTH / 4, 50 });
	global_UI_sprites.push_back(titleText);
	
	// Adding buttons
	// Button A
	cSpriteButton* buttonA = new cSpriteButton();
	buttonA->setTexture(cTextureMgr::getInstance()->getTexture("Button"));
	buttonA->setSpriteDimensions(WINDOW_WIDTH / 10, WINDOW_WIDTH / 20);
	buttonA->setSpritePos({ WINDOW_WIDTH / 2 - buttonA->getSpriteDimensions().w/2, 200 });
	buttonA->setCallbackFunction(&StartRaceScene);
	global_UI_sprites.push_back(buttonA);
	buttonContr = new cButtonController(buttonA);
	// Button A text
	cSpriteText* bAText = new cSpriteText(theRenderer, cFontMgr::getInstance()->getFont("pirate"), "raceTxt");
	bAText->setText("RACE");
	bAText->setSpriteDimensions(buttonA->getSpriteDimensions().w, buttonA->getSpriteDimensions().h);
	bAText->setSpritePos(buttonA->getPosition());
	global_UI_sprites.push_back(bAText);

	// Button B
	cSpriteButton* buttonB = new cSpriteButton();
	buttonB->setTexture(cTextureMgr::getInstance()->getTexture("Button"));
	buttonB->setSpriteDimensions(WINDOW_WIDTH / 10, WINDOW_WIDTH / 20);
	buttonB->setSpritePos({ WINDOW_WIDTH / 2 - buttonB->getSpriteDimensions().w / 2, 275 });
	buttonB->setCallbackFunction(&QuitGame);
	global_UI_sprites.push_back(buttonB);
	buttonContr->addButton(buttonB);
	// Button B text
	cSpriteText* bBText = new cSpriteText(theRenderer, cFontMgr::getInstance()->getFont("pirate"), "exitTxt");
	bBText->setText("EXIT");
	bBText->setSpriteDimensions(buttonB->getSpriteDimensions().w, buttonB->getSpriteDimensions().h);
	bBText->setSpritePos(buttonB->getPosition());
	global_UI_sprites.push_back(bBText);

}


cSceneStart::~cSceneStart()
{
	// Cleaning up textures that were loaded for this specific scene.
	cTextureMgr::getInstance()->deleteTexture("Background");


	// Cleaning up the button controller
	delete buttonContr;
}

void cSceneStart::activate()
{
	// Registering button controller to all channels.
	int numberOfPlayers = Input::GetNumberOfPlayers();
	for (int i = 0; i < numberOfPlayers; ++i)
	{
		Input::RegisterChannelListener(buttonContr, i);
	}
}

void cSceneStart::deactivate()
{
	// Unregistering button controller
	Input::UnRegisterChannelListener(buttonContr);
}
