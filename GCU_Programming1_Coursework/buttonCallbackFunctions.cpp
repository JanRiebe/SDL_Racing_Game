#include "buttonCallbackFunctions.h"
#include "cGame.h"


void GoToStartScreen()
{
	cGame::getInstance()->setActiveScene("start");
}


void StartRaceScene()
{
	cGame::getInstance()->setActiveScene("race");
}

void QuitGame()
{
	cGame::getInstance()->QuitGame();
}