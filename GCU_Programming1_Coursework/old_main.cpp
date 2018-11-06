/*
Written by Jan Riebe
Extended from this tutorial:
http://lazyfoo.net/tutorials/SDL/11_clip_rendering_and_sprite_sheets/index.php
*/
/*
//Using SDL, SDL_image and standard IO
#include <SDL.h>
#include <SDL_image.h>		// For loading other images than bmp
#include <stdio.h>
#include <string>
#include <chrono>
#include "LTexture.h"
#include "AnimatedTexture.h"

using namespace std::chrono;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Key press surfaces constants 
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};


//Starts up SDL and creates window
bool init();
//Loads media 
bool loadMedia();
//Frees media and shuts down SDL
void close();
// Returns the seconds since the last frame.
double getElapsedSeconds();


//The window we'll be rendering to 
SDL_Window* gWindow = NULL;
//The window renderer 
SDL_Renderer* gRenderer = NULL;
//Scene textures 
AnimatedTexture gAnimatedTexture_up;
AnimatedTexture gAnimatedTexture_down;
AnimatedTexture gAnimatedTexture_left;
AnimatedTexture gAnimatedTexture_right;
//Time when the last frame was drawn
time_point< high_resolution_clock > lastTime;




int main(int argc, char* args[]) {		// SLD requires a main with these types of arguments

										//Start up SDL and create window 
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media 
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{


			//Main loop flag 
			bool quit = false;
			//Event handler 
			SDL_Event e;

			int time = 0;

			//While application is running 
			while (!quit) {
				double elapsedTime = getElapsedSeconds();

				//Handle events on queue 
				while (SDL_PollEvent(&e) != 0) // polls an event from the event queue and puts it into e (the union we created before)
				{
					//User requests quit 
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN)
					{
						// Switching off all animations,
						// to then switch on the right one only.
						gAnimatedTexture_up.play(false);
						gAnimatedTexture_down.play(false);
						gAnimatedTexture_left.play(false);
						gAnimatedTexture_right.play(false);

						//Select surfaces based on key press 
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							gAnimatedTexture_up.play(true);
							break;
						case SDLK_DOWN:
							gAnimatedTexture_down.play(true);
							break;
						case SDLK_LEFT:
							gAnimatedTexture_left.play(true);
							break;
						case SDLK_RIGHT:
							gAnimatedTexture_right.play(true);
							break;
						default:

							break;
						}
					}
				}

				// Update objects
				gAnimatedTexture_up.update(elapsedTime);
				gAnimatedTexture_down.update(elapsedTime);
				gAnimatedTexture_left.update(elapsedTime);
				gAnimatedTexture_right.update(elapsedTime);

				//Clear screen 
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render animated texture in the middle of the screen.
				if (gAnimatedTexture_up.isPlaying())
					gAnimatedTexture_up.renderAnimated(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
				else if (gAnimatedTexture_right.isPlaying())
					gAnimatedTexture_right.renderAnimated(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
				else if (gAnimatedTexture_left.isPlaying())
					gAnimatedTexture_left.renderAnimated(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
				else
					gAnimatedTexture_down.renderAnimated(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

				//Update screen 
				SDL_RenderPresent(gRenderer);
			}
		}



	}
	//Free resources and close SDL 
	close();

	return 0;
}



bool init()
{
	//Initialization flag 
	bool success = true;
	//Initialize SDL 
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window 
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window 
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{

				//Initialize renderer color 
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}



bool loadMedia()
{
	//Loading success flag 
	bool success = true;


	//Load sprite sheet texture 
	if (!gAnimatedTexture_up.loadFromFile("Images/Charactervector.png", 4, 4, 4, 4))
	{
		printf("Failed to load sprite sheet texture!\n");
		success = false;
	}
	//Load sprite sheet texture 
	if (!gAnimatedTexture_down.loadFromFile("Images/Charactervector.png", 4, 4, 0, 4))
	{
		printf("Failed to load sprite sheet texture!\n");
		success = false;
	}
	//Load sprite sheet texture 
	if (!gAnimatedTexture_left.loadFromFile("Images/Charactervector.png", 4, 4, 8, 4))
	{
		printf("Failed to load sprite sheet texture!\n");
		success = false;
	}
	//Load sprite sheet texture 
	if (!gAnimatedTexture_right.loadFromFile("Images/Charactervector.png", 4, 4, 12, 4))
	{
		printf("Failed to load sprite sheet texture!\n");
		success = false;
	}

	return success;
}




void close()
{
	//Free loaded images 
	gAnimatedTexture_up.free();
	gAnimatedTexture_down.free();
	gAnimatedTexture_left.free();
	gAnimatedTexture_right.free();

	//Destroy window 
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	//Quit SDL subsystems 
	IMG_Quit();
	SDL_Quit();
}




double getElapsedSeconds()
{
	time_point< high_resolution_clock > currentTime = high_resolution_clock::now();
	duration< double > deltaTime = currentTime - lastTime;
	lastTime = currentTime;
	return deltaTime.count();
}


















void LTexture::render(int x, int y, SDL_Rect* clip)
{
	//Set rendering space and render to screen 
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions 
	if (clip != NULL)
	{
		renderQuad.w = clip->w; renderQuad.h = clip->h;
	}
	//Render to screen 
	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}



bool LTexture::loadFromFile(std::string path)
{

	//Get rid of preexisting texture
	free();
	//The final texture 
	SDL_Texture* newTexture = NULL;
	//Load image at specified path 
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image 
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));	// The last argument is a pixel containing the color used for keying. SDL_MapRGB creates a pixel.
																										//Create texture from surface pixels 
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		//Get rid of old loaded surface 
		SDL_FreeSurface(loadedSurface);
	}
	//Return success 
	mTexture = newTexture;
	return mTexture != NULL;
}
*/