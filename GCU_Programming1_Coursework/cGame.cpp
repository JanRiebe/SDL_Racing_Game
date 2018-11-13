/*
==================================================================================
cGame.cpp
==================================================================================
*/
#include "cGame.h"

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();


/*
=================================================================================
Constructor
=================================================================================
*/
cGame::cGame()
{

}
/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cGame* cGame::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cGame();
	}
	return cGame::pInstance;
}


void cGame::initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	this->m_lastTime = high_resolution_clock::now();

	// Clear the buffer with a black background
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);

	theTextureMgr->setRenderer(theRenderer);
	// Store the textures
	theTextureMgr->addTexture("Charactervector", "Images\\Charactervector.png");

	/*
	cSprite* tmpSprite = new cSprite();
	tmpSprite->setSpritePos({ 0,0 });
	tmpSprite->setTexture(theTextureMgr->getTexture("Charactervector"));
	tmpSprite->setSpriteDimensions(theTextureMgr->getTexture("Charactervector")->getTWidth(), theTextureMgr->getTexture("Charactervector")->getTHeight());
	sprites.push_back(tmpSprite);

	cSpriteMap* tmpSpriteMap = new cSpriteMap();
	tmpSpriteMap->setSpritePos({ 100,0 });
	tmpSpriteMap->setTexture(theTextureMgr->getTexture("Charactervector"));
	tmpSpriteMap->setSpriteScale({0.3f, 1.0f});
	tmpSpriteMap->loadMap("foo");
	tmpSpriteMap->setSheetGrid(4, 4);
	sprites.push_back(tmpSpriteMap);
	*/
	cSpriteAnimation* tmpSpriteAnim = new cSpriteAnimation();
	tmpSpriteAnim->setTexture(theTextureMgr->getTexture("Charactervector"));
	tmpSpriteAnim->setSpriteScale({0.1f, 0.1f});
	tmpSpriteAnim->setSheetGrid(4, 4);
	tmpSpriteAnim->setSpeed(4.0);
	tmpSpriteAnim->trim(4, 4);
	tmpSpriteAnim->play();
	sprites.push_back(tmpSpriteAnim);
	
}

void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	bool loop = true;

	while (loop)
	{
		//We get the time that passed since the last frame
		double elapsedTime = this->getElapsedSeconds();

		loop = this->getInput(loop);
		this->update(elapsedTime);
		this->render(theSDLWND, theRenderer);
	}
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	SDL_RenderClear(theRenderer);
	
	// Rendering all sprites
	vector<cSprite*>::iterator it = sprites.begin();
	for (it; it != sprites.end(); ++it) {
		(*it)->render(theRenderer, &camera);
	}

	SDL_RenderPresent(theRenderer);
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre)
{

	SDL_RenderPresent(theRenderer);
}

void cGame::update()
{

}

void cGame::update(double deltaTime)
{
	// Updating all sprites
	vector<cSprite*>::iterator it = sprites.begin();
	for (it; it != sprites.end(); ++it) {
		(*it)->update(deltaTime);
	}
}

bool cGame::getInput(bool theLoop)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			theLoop = false;
		}

		//TODO use my input system here

		switch (event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
				{
					cout << "Left mouse button pressed.\n";
				}
				break;
				case SDL_BUTTON_RIGHT:
					break;
				default:
					break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
				{
					cout << "Left mouse button released.\n";
				}
				break;
				case SDL_BUTTON_RIGHT:
					break;
				default:
					break;
				}
				break;
			case SDL_MOUSEMOTION:
			{
			}
			break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					theLoop = false;
					break;
				default:
					break;
				}

			default:
				break;
		}

	}
	return theLoop;
}

double cGame::getElapsedSeconds()
{
	this->m_CurrentTime = high_resolution_clock::now();
	this->deltaTime = (this->m_CurrentTime - this->m_lastTime);
	this->m_lastTime = this->m_CurrentTime;
	return deltaTime.count();
}

void cGame::cleanUp(SDL_Window* theSDLWND)
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(theSDLWND);

	// Destroy the window
	SDL_DestroyWindow(theSDLWND);

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}

