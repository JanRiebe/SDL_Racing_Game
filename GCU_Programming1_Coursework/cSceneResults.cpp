#include "cSceneResults.h"
#include "GameConstants.h"
#include "gameHeaders.h"
#include "inputHeaders.h"
#include "buttonCallbackFunctions.h"




cSceneResults::cSceneResults(SDL_Renderer* theRenderer)
{
	Input::RegisterDevice(KEYBOARD_ARROWS, 0);	//tmp here, should be on the registration screen
	Input::RegisterDevice(KEYBOARD_WASD, 1);	//tmp here, should be on the registration screen



	// loading textures
	cTextureMgr::getInstance()->addTexture("Background", "Images\\tmp_menu_bg.jpg");



	// loading sounds



	// Creating camera
	cCamera* newCam = new cCamera();
	newCam->SetViewport({ 0,0,WINDOW_WIDTH,WINDOW_HEIGHT });
	cameras.push_back(newCam);



	// Creating sprites

	// Background
	cSprite * background = new cSprite();
	background->setTexture(cTextureMgr::getInstance()->getTexture("Background"));
	background->setSpriteDimensions(WINDOW_WIDTH, WINDOW_HEIGHT);
	sprites.push_back(background);

	// Adding title text sprite
	cSpriteText* titleText = new cSpriteText(theRenderer, cFontMgr::getInstance()->getFont("pirate"), "resultTitleTxt");
	titleText->setText("Score");
	titleText->setSpriteDimensions(WINDOW_WIDTH / 5, WINDOW_WIDTH / 10);
	titleText->setSpritePos({ WINDOW_WIDTH / 2 - titleText->getSpriteDimensions().w/2, 50 });
	uiSprites[newCam].push_back(titleText);

	// Adding buttons
	// Button A
	cSpriteButton* buttonA = new cSpriteButton();
	buttonA->setTexture(cTextureMgr::getInstance()->getTexture("Button"));
	buttonA->setSpriteDimensions(WINDOW_WIDTH / 3, WINDOW_WIDTH / 20);
	buttonA->setSpritePos({ WINDOW_WIDTH / 2 - buttonA->getSpriteDimensions().w / 2, WINDOW_HEIGHT - 100 });
	buttonA->setCallbackFunction(&GoToStartScreen);
	uiSprites[newCam].push_back(buttonA);
	buttonContr = new cButtonController(buttonA);
	// Button A text
	cSpriteText* bAText = new cSpriteText(theRenderer, cFontMgr::getInstance()->getFont("pirate"), "toTitleTxt");
	bAText->setText("to Title screen");
	bAText->setSpriteDimensions(buttonA->getSpriteDimensions().w, buttonA->getSpriteDimensions().h);
	bAText->setSpritePos(buttonA->getPosition());
	uiSprites[newCam].push_back(bAText);

}


cSceneResults::~cSceneResults()
{
	// Cleaning up textures that were loaded for this specific scene.
	cTextureMgr::getInstance()->deleteTexture("Background");


	// Cleaning up the button controller
	delete buttonContr;
}

void cSceneResults::activate()
{
	// Registering button controller to all channels.
	int numberOfPlayers = Input::GetNumberOfPlayers();
	for (int i = 0; i < numberOfPlayers; ++i)
	{
		Input::RegisterChannelListener(buttonContr, i);
	}
}

void cSceneResults::deactivate()
{
	// Unregistering button controller
	Input::UnRegisterChannelListener(buttonContr);
}
