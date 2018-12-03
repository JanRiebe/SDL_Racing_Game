#include "cSceneStart.h"
#include "GameConstants.h"
#include "gameHeaders.h"
#include "inputHeaders.h"
#include "buttonCallbackFunctions.h"




cSceneStart::cSceneStart(SDL_Renderer* theRenderer): cScene(theRenderer)
{


	Input::RegisterDevice(KEYBOARD_ARROWS, 0);	//tmp here, should be on the registration screen
	Input::RegisterDevice(KEYBOARD_WASD, 1);	//tmp here, should be on the registration screen



												// loading textures
	cTextureMgr::getInstance()->addTexture("Menu_Background_City", "Images\\architecture-buildings-city-169647_small.png");
	cTextureMgr::getInstance()->addTexture("Keys_WASD", "Images\\buttons_wasd.png");
	cTextureMgr::getInstance()->addTexture("Keys_Arrows", "Images\\buttons_arrows.png");



	// loading sounds



	// Creating camera


	// Creating sprites

	// Background
	cSprite * background = new cSprite();
	background->setTexture(cTextureMgr::getInstance()->getTexture("Menu_Background_City"));
	background->setSpriteDimensions(WINDOW_WIDTH, WINDOW_HEIGHT);
	global_UI_sprites.push_back(background);

	// Adding title text sprite
	cSpriteText* titleText = new cSpriteText(theRenderer, cFontMgr::getInstance()->getFont("main_font"), "titleTxt");
	titleText->setText("Jan's fun and educational racing game");
	titleText->setSpriteDimensions(WINDOW_WIDTH / 2, WINDOW_WIDTH / 10);
	titleText->setSpritePos({ WINDOW_WIDTH / 4, 50 });
	global_UI_sprites.push_back(titleText);

	// Adding buttons
	// Button A
	cSpriteButton* buttonA = new cSpriteButton();
	buttonA->setTexture(cTextureMgr::getInstance()->getTexture("Button"));
	buttonA->setSpriteDimensions(WINDOW_WIDTH / 10, WINDOW_WIDTH / 20);
	buttonA->setSpritePos({ WINDOW_WIDTH / 2 - buttonA->getSpriteDimensions().w / 2, 200 });
	buttonA->setCallbackFunction(&StartRaceScene);
	global_UI_sprites.push_back(buttonA);
	buttonContr = new cButtonController(buttonA);
	// Button A text
	cSpriteText* bAText = new cSpriteText(theRenderer, cFontMgr::getInstance()->getFont("main_font"), "raceTxt");
	bAText->setText("RACE");
	bAText->setSpriteDimensions(buttonA->getSpriteDimensions().w, buttonA->getSpriteDimensions().h);
	bAText->setSpritePos(buttonA->getPosition());
	global_UI_sprites.push_back(bAText);


	// Button C
	cSpriteButton* buttonC = new cSpriteButton();
	buttonC->setTexture(cTextureMgr::getInstance()->getTexture("Button"));
	buttonC->setSpriteDimensions(WINDOW_WIDTH / 10, WINDOW_WIDTH / 20);
	buttonC->setSpritePos({ WINDOW_WIDTH / 2 - buttonC->getSpriteDimensions().w / 2, 350 });
	buttonC->setCallbackFunction(&QuitGame);
	global_UI_sprites.push_back(buttonC);
	buttonContr->addButton(buttonC);
	// Button C text
	cSpriteText* bCText = new cSpriteText(theRenderer, cFontMgr::getInstance()->getFont("main_font"), "exitTxt");
	bCText->setText("EXIT");
	bCText->setSpriteDimensions(buttonC->getSpriteDimensions().w, buttonC->getSpriteDimensions().h);
	bCText->setSpritePos(buttonC->getPosition());
	global_UI_sprites.push_back(bCText);


	// Button B
	cSpriteButton* buttonB = new cSpriteButton();
	buttonB->setTexture(cTextureMgr::getInstance()->getTexture("Button"));
	buttonB->setSpriteDimensions(WINDOW_WIDTH / 10, WINDOW_WIDTH / 20);
	buttonB->setSpritePos({ WINDOW_WIDTH / 2 - buttonB->getSpriteDimensions().w / 2, 275 });
	buttonB->setCallbackFunction(&GoToHighscoreScreen);
	global_UI_sprites.push_back(buttonB);
	buttonContr->addButton(buttonB);
	// Button B text
	cSpriteText* bBText = new cSpriteText(theRenderer, cFontMgr::getInstance()->getFont("main_font"), "startToHighscoresTxt");
	bBText->setText("Highscores");
	bBText->setSpriteDimensions(buttonB->getSpriteDimensions().w, buttonB->getSpriteDimensions().h);
	bBText->setSpritePos(buttonB->getPosition());
	global_UI_sprites.push_back(bBText);


	// Key help sprites
	// WASD
	cSprite * keys = new cSprite();
	keys->setTexture(cTextureMgr::getInstance()->getTexture("Keys_WASD"));
	keys->setSpritePos({100, WINDOW_HEIGHT/2 - keys->getSpriteDimensions().h/2});
	global_UI_sprites.push_back(keys);
	// Arrows
	keys = new cSprite();
	keys->setTexture(cTextureMgr::getInstance()->getTexture("Keys_Arrows"));
	keys->setSpritePos({WINDOW_WIDTH - keys->getSpriteDimensions().w - 100, WINDOW_HEIGHT / 2 - keys->getSpriteDimensions().h / 2 });
	global_UI_sprites.push_back(keys);
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

	// Playing music
	cSoundMgr::getInstance()->getSnd("menu_music")->play(-1);
}

void cSceneStart::deactivate()
{
	// Unregistering button controller
	Input::UnRegisterChannelListener(buttonContr);
}
