#include "cSceneHighscores.h"
#include "GameConstants.h"
#include "gameHeaders.h"
#include "inputHeaders.h"
#include "buttonCallbackFunctions.h"


cSceneHighscores::cSceneHighscores(SDL_Renderer* theRenderer) :cScene(theRenderer)
{

	Input::RegisterDevice(KEYBOARD_ARROWS, 0);	//tmp here, should be on the registration screen
	Input::RegisterDevice(KEYBOARD_WASD, 1);	//tmp here, should be on the registration screen



												// loading textures
	cTextureMgr::getInstance()->addTexture("Menu_Background_Fog", "Images\\action-arrow-asphalt-706103_small.png");



	// loading sounds



	// Creating sprites

	// Background
	cSprite * background = new cSprite();
	background->setTexture(cTextureMgr::getInstance()->getTexture("Menu_Background_Fog"));
	background->setSpriteDimensions(WINDOW_WIDTH, WINDOW_HEIGHT);
	global_UI_sprites.push_back(background);

	// Adding title text sprite
	cSpriteText* titleText = new cSpriteText(theRenderer, cFontMgr::getInstance()->getFont("main_font"), "highscoreTitleText");
	titleText->setText("Highscores");
	titleText->setSpriteDimensions(WINDOW_WIDTH / 5, WINDOW_WIDTH / 10);
	titleText->setSpritePos({ WINDOW_WIDTH - titleText->getSpriteDimensions().w - 100, 0 });
	global_UI_sprites.push_back(titleText);


	// Adding highscore text sprites
	for (int i = 0; i < HIGHSCORE_LIST_ENTRIES; i++)
	{
		highscoreTexts[i] = new cSpriteText(theRenderer, cFontMgr::getInstance()->getFont("main_font"), "highscore_entry_text_" + i);
		highscoreTexts[i]->setSpriteDimensions(WINDOW_WIDTH / 2, (WINDOW_HEIGHT - 100) / HIGHSCORE_LIST_ENTRIES);
		highscoreTexts[i]->setSpritePos({ 100, highscoreTexts[i]->getSpriteDimensions().h * i + 50 });
		global_UI_sprites.push_back(highscoreTexts[i]);
	}


	// Adding buttons
	// Button A
	cSpriteButton* buttonA = new cSpriteButton();
	buttonA->setTexture(cTextureMgr::getInstance()->getTexture("Button"));
	buttonA->setSpriteDimensions(WINDOW_WIDTH / 3, WINDOW_WIDTH / 20);
	buttonA->setSpritePos({ WINDOW_WIDTH - buttonA->getSpriteDimensions().w - 50, WINDOW_HEIGHT - 100 });
	buttonA->setCallbackFunction(&GoToStartScreen);
	global_UI_sprites.push_back(buttonA);
	buttonContr = new cButtonController(buttonA);
	// Button A text
	cSpriteText* bAText = new cSpriteText(theRenderer, cFontMgr::getInstance()->getFont("main_font"), "highscoresToTitleTxt");
	bAText->setText("to Title screen");
	bAText->setSpriteDimensions(buttonA->getSpriteDimensions().w, buttonA->getSpriteDimensions().h);
	bAText->setSpritePos(buttonA->getPosition());
	global_UI_sprites.push_back(bAText);


}


cSceneHighscores::~cSceneHighscores()
{
	// Cleaning up textures that were loaded for this specific scene.
	cTextureMgr::getInstance()->deleteTexture("Menu_Background_Fog");


	// Cleaning up the button controller
	delete buttonContr;
}

void cSceneHighscores::activate()
{
	// Registering button controller to all channels.
	int numberOfPlayers = Input::GetNumberOfPlayers();
	for (int i = 0; i < numberOfPlayers; ++i)
	{
		Input::RegisterChannelListener(buttonContr, i);
	}

	// Showing the highscore
	cScoreMgr::getInstance()->LoadScores();
	for (int i = 0; i < HIGHSCORE_LIST_ENTRIES; i++)
	{
		highscoreTexts[i]->setText(cScoreMgr::getInstance()->getHighscoreEntry(i));
	}
}

void cSceneHighscores::deactivate()
{
	// Unregistering button controller
	Input::UnRegisterChannelListener(buttonContr);
}

