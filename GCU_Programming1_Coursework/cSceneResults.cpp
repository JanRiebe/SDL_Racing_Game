#include "cSceneResults.h"
#include "GameConstants.h"
#include "gameHeaders.h"
#include "inputHeaders.h"
#include "buttonCallbackFunctions.h"




cSceneResults::cSceneResults(SDL_Renderer* theRenderer) :cScene(theRenderer)
{



												// loading textures
	cTextureMgr::getInstance()->addTexture("Menu_Background_Black", "Images\\auto-automobile-automotive-919073_small.png");



	// loading sounds



	// Creating sprites

	// Background
	cSprite * background = new cSprite();
	background->setTexture(cTextureMgr::getInstance()->getTexture("Menu_Background_Black"));
	background->setSpriteDimensions(WINDOW_WIDTH, WINDOW_HEIGHT);
	global_UI_sprites.push_back(background);

	// Adding title text sprite
	cSpriteText* titleText = new cSpriteText(theRenderer, cFontMgr::getInstance()->getFont("main_font"), "resultTitleTxt");
	titleText->setText("Score");
	titleText->setSpriteDimensions(WINDOW_WIDTH / 5, WINDOW_WIDTH / 10);
	titleText->setSpritePos({ WINDOW_WIDTH / 2 - titleText->getSpriteDimensions().w / 2, 50 });
	global_UI_sprites.push_back(titleText);

	// Adding score text sprites
	scoreTexts[0] = new cSpriteText(theRenderer, cFontMgr::getInstance()->getFont("main_font"), "scoreTxt_A");
	scoreTexts[0]->setSpriteDimensions(WINDOW_WIDTH / 5, WINDOW_HEIGHT / 4);
	scoreTexts[0]->setSpritePos({ WINDOW_WIDTH / 4 - scoreTexts[0]->getSpriteDimensions().w / 2, WINDOW_HEIGHT / 2 - scoreTexts[0]->getSpriteDimensions().h / 2 });
	global_UI_sprites.push_back(scoreTexts[0]);

	scoreTexts[1] = new cSpriteText(theRenderer, cFontMgr::getInstance()->getFont("main_font"), "scoreTxt_B");
	scoreTexts[1]->setSpriteDimensions(WINDOW_WIDTH / 5, WINDOW_HEIGHT / 4);
	scoreTexts[1]->setSpritePos({ 3 * WINDOW_WIDTH / 4 - scoreTexts[1]->getSpriteDimensions().w / 2, WINDOW_HEIGHT / 2 - scoreTexts[1]->getSpriteDimensions().h / 2 });
	global_UI_sprites.push_back(scoreTexts[1]);


	// Adding buttons
	// Button A
	cSpriteButton* buttonA = new cSpriteButton();
	buttonA->setTexture(cTextureMgr::getInstance()->getTexture("Button"));
	buttonA->setSpriteDimensions(WINDOW_WIDTH / 3, WINDOW_WIDTH / 20);
	buttonA->setSpritePos({ WINDOW_WIDTH / 2 - buttonA->getSpriteDimensions().w / 2, WINDOW_HEIGHT - buttonA->getSpriteDimensions().h - 100 });
	buttonA->setCallbackFunction(&GoToStartScreen);
	global_UI_sprites.push_back(buttonA);
	buttonContr = new cButtonController(buttonA);
	// Button A text
	cSpriteText* bAText = new cSpriteText(theRenderer, cFontMgr::getInstance()->getFont("main_font"), "toTitleTxt");
	bAText->setText("to Title screen");
	bAText->setSpriteDimensions(buttonA->getSpriteDimensions().w, buttonA->getSpriteDimensions().h);
	bAText->setSpritePos(buttonA->getPosition());
	global_UI_sprites.push_back(bAText);
	// Button B
	cSpriteButton* buttonB = new cSpriteButton();
	buttonB->setTexture(cTextureMgr::getInstance()->getTexture("Button"));
	buttonB->setSpriteDimensions(WINDOW_WIDTH / 3, WINDOW_WIDTH / 20);
	buttonB->setSpritePos({ WINDOW_WIDTH / 2 - buttonB->getSpriteDimensions().w / 2, WINDOW_HEIGHT - 50 });
	buttonB->setCallbackFunction(&GoToHighscoreScreen);
	global_UI_sprites.push_back(buttonB);
	buttonContr->addButton(buttonB);
	// Button B text
	cSpriteText* bBText = new cSpriteText(theRenderer, cFontMgr::getInstance()->getFont("main_font"), "toHighscoresTxt");
	bBText->setText("Highscores");
	bBText->setSpriteDimensions(buttonB->getSpriteDimensions().w, buttonB->getSpriteDimensions().h);
	bBText->setSpritePos(buttonB->getPosition());
	global_UI_sprites.push_back(bBText);

}


cSceneResults::~cSceneResults()
{
	// Cleaning up textures that were loaded for this specific scene.
	cTextureMgr::getInstance()->deleteTexture("Menu_Background_Black");


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

	// Showing the score
	scoreTexts[0]->setText(cScoreMgr::getInstance()->getScore(POLICE));
	scoreTexts[1]->setText(cScoreMgr::getInstance()->getScore(CRIMINALS));

	// Play music
	cSoundMgr::getInstance()->getSnd("result_music")->play(1);
}

void cSceneResults::deactivate()
{
	// Unregistering button controller
	Input::UnRegisterChannelListener(buttonContr);
}
