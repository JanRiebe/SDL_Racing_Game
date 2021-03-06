/*
==================================================================================
cGame.cpp
==================================================================================
*/
#include "cGame.h"
#include "inputHeaders.h"

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
static cFontMgr* theFontMgr = cFontMgr::getInstance();
static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();



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

void cGame::destroyScene(string sceneName)
{
	// Research on deleting element from map: https://stackoverflow.com/questions/5460678/whats-the-best-way-to-delete-an-entry-mapint-a
	map<string, cScene *>::iterator it = scenes.find(sceneName);
	if (it != scenes.end()) {
		delete it->second;
		scenes.erase(it);
	}	
	cout << "successfully deleted scene " << sceneName << endl;
}

void cGame::addScene(string sceneName, cScene * scene)
{
	cout << "adding scene " << sceneName << endl;
	// If there already is a scene with this name,
	// delete the existing scene.
	if(scenes.count(sceneName)>0)
	destroyScene(sceneName);

	// Adding the new scene.
	scenes.insert(pair<string, cScene*>(sceneName, scene));
}



SDL_Renderer * cGame::getRenderer()
{
	return theRenderer;
}

void cGame::QuitGame()
{
	loop = false;
}


void cGame::initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	this->theRenderer = theRenderer;

	this->m_lastTime = high_resolution_clock::now();

	// Hiding the mouse cursor
	SDL_ShowCursor(SDL_DISABLE);

	// Clear the buffer with a black background
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);

	// Initialising font manager
	theFontMgr->initFontLib();

	// Initialising sound manager
	theSoundMgr->initMixer();

	// Initialising texture manager
	theTextureMgr->setRenderer(theRenderer);
	// Store the textures that are used globally throughout the game.
	theTextureMgr->addTexture("Charactervector", "Images\\Charactervector.png");
	theTextureMgr->addTexture("Button", "Images\\button.png");

	theSoundMgr->add("menu_music", "Audio\\243978__orangefreesounds__deep-drive-synth-loop.wav", soundType::music);
	theSoundMgr->add("racing_music", "Audio\\116621__timbre__remix-3-of-116327-ajc-heartattack-b1.flac", soundType::music);
	theSoundMgr->add("result_music", "Audio\\241441__foolboymedia__ocean-drift.wav", soundType::music);
	theSoundMgr->add("crash_fx", "Audio\\67617__qubodup__metal-crash-collision.wav", soundType::sfx);

	// Adding a text texture
	cFontMgr::getInstance()->addFont("main_font", "Fonts\\neon_pixel-7.ttf", 64);
	SDL_Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	SDL_Color transp = color;
	transp.a = 0;
	theTextureMgr->addTexture("testText0",
		cFontMgr::getInstance()->getFont("main_font")->createTextTexture(theRenderer, "Test", textType::blended, color, transp)
	);
	theTextureMgr->addTexture("testText1",
		cFontMgr::getInstance()->getFont("main_font")->createTextTexture(theRenderer, "some other text that is super long", textType::blended, color, transp)
	);

	addScene("start", new cSceneStart(theRenderer));
	addScene("result", new cSceneResults(theRenderer));
	addScene("highscores", new cSceneHighscores(theRenderer));
	setActiveScene("start");
}

void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	loop = true;

	while (loop)
	{
		//We get the time that passed since the last frame
		double elapsedTime = this->getElapsedSeconds();

		// Evaluating whether to continue the loop,
		// by considering the return value of getInput
		// and the side effects of getInput on loop.
		// Note that the order is important.
		loop = this->getInput(loop) && loop;

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
	// Deleting scenes
	//TODO

	// Delete our OpengL context
	SDL_GL_DeleteContext(theSDLWND);

	// Destroy the window
	SDL_DestroyWindow(theSDLWND);

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}

