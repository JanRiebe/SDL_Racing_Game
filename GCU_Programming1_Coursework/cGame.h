#ifndef _GAME_H
#define _GAME_H

/*
==================================================================================
cGame.h
==================================================================================
*/

#include <SDL.h>

// Game specific includes
#include "gameHeaders.h"


using namespace std;

class cGame
{
public:
	cGame();

	void initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void cleanUp(SDL_Window* theSDLWND);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre);
	void update();
	void update(double deltaTime);
	bool getInput(bool theLoop);
	double getElapsedSeconds();

	static cGame* getInstance();

	// Sets the active scene to be updated and rendered.
	void setActiveScene(string sceneName);
	
	// Ends the game
	void QuitGame();


private:
	static cGame* pInstance;

	// Whether the main game loop is running. Once this is is false, the game ends.
	bool loop;

	// for framerates
	time_point< high_resolution_clock > m_lastTime;
	time_point< high_resolution_clock > m_CurrentTime;
	duration< double > deltaTime;

	// game related variables
	vector<LPCSTR> textureName;
	vector<LPCSTR> texturesToUse;

	vector<cSprite*> sprites;

	map<string, cScene*> scenes;
	cScene* activeScene;
	
	cCamera camera;

};

#endif
