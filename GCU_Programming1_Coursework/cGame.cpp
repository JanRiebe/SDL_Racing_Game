/*
==================================================================================
cGame.cpp
==================================================================================
*/
#include "cGame.h"
#include "inputHeaders.h"

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();


/*
=================================================================================
Constructor
=================================================================================
*/
cGame::cGame()
{
	activeScene = NULL;
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

void cGame::setActiveScene(string sceneName)
{
	if (scenes.count(sceneName) != 0)
	{
		// Deactivating the old active scene, if there is one.
		if(activeScene)
			activeScene->deactivate();
		// Setting the new active scene.
		activeScene = scenes[sceneName];
		// Activating the new active scene.
		activeScene->activate();
	}
	else
		cout << "Failed to activate scene '" << sceneName << "'. No scene with this name found." << endl;
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
	
	scenes["race"] = new cSceneRacing(theTextureMgr);
	setActiveScene("race");
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
	
	if(activeScene)
		activeScene->render(theRenderer);

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
	if(activeScene)
		activeScene->update(deltaTime);
}

bool cGame::getInput(bool theLoop)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		// Handling events that are not related to user input.
		// Such as quitting.
		if (event.type == SDL_QUIT)
		{
			theLoop = false;
		}
		// Passing the sdl event to the input manager.
		Input::SDLEventIn(event);
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

