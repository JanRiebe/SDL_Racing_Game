#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

// SDL2 Headers
#include <SDL.h>
#include <SDL_image.h>		// For loading other images than bmp
#include <stdio.h>
#include <string>
#include <chrono>
#include "LTexture.h"
#include "AnimatedTexture.h"

#include "cSDL2WNDManager.h"
#include "cGame.h"

using namespace std;

//This is the SDL window
static cSDL2WNDManager* pgmWNDMgr = cSDL2WNDManager::getInstance();

//This is the our Game
static cGame* theGame = cGame::getInstance();

int main(int argc, char *argv[])
{
	if (!pgmWNDMgr->initWND(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT))
		return -1;

	theGame->initialise(pgmWNDMgr->getSDLWindow(), pgmWNDMgr->getSDLRenderer());

	theGame->run(pgmWNDMgr->getSDLWindow(), pgmWNDMgr->getSDLRenderer());

	theGame->cleanUp(pgmWNDMgr->getSDLWindow());

	return 0;
}


//TODO test by recreating previous animation player in new framework
//TODO document changes