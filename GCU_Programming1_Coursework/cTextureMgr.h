/*
=================
cTextureMgr.h
- Header file for class definition - SPECIFICATION
- Header file for the cTextureMgr class
=================
*/
#ifndef _CTEXTUREMGR_H
#define _CTEXTUREMGR_H
#include "GameConstants.h"
#include "cTexture.h"
#include "cTextureAnimated.h"

class cTextureMgr
{
private:
	static cTextureMgr* pInstance;
	map<LPCSTR, cTexture*> textureList;
	map<LPCSTR, cTextureAnimated*> animatedTextureList;
	SDL_Renderer* theSDLRenderer;

public:
	static cTextureMgr* getInstance();
	cTextureMgr();
	cTextureMgr(SDL_Renderer* theRenderer);
	~cTextureMgr();
	void addTexture(LPCSTR txtName, LPCSTR theFilename);
	//Adds a texture in a cTextureAnimated wrapper. Parameters rows and collums define how many tiles there are in the animation sprite sheet.
	void addTextureAnimated(LPCSTR txtName, LPCSTR theFilename, int rows, int collums);
	cTexture* getTexture(LPCSTR textureName);		// return the texture.
	//Returns a texture in a cTextureAnimated wrapper.
	cTextureAnimated* getTextureAnimated(LPCSTR textureName);		// return the texture.
	void setRenderer(SDL_Renderer* ptheRenderer); // Set the renderer
	void deleteTextures();						// Delete all textures;
};
#endif