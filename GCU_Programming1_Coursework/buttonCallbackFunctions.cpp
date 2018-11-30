#include "buttonCallbackFunctions.h"
#include "cGame.h"


void GoToStartScreen()
{
	// Destroying the racing scene.
	cGame::getInstance()->destroyScene("race");
	// Setting active scene to start scene.
	cGame::getInstance()->setActiveScene("start");
}

void GoToHighscoreScreen()
{
	cGame::getInstance()->setActiveScene("highscores");
}


void StartRaceScene()
{
	// Creating a racing scene.
	cGame::getInstance()->addScene("race", new cSceneRacing(cGame::getInstance()->getRenderer()));
	// Setting the racting scene as active scene.
	cGame::getInstance()->setActiveScene("race");
}

void QuitGame()
{
	cGame::getInstance()->QuitGame();
}