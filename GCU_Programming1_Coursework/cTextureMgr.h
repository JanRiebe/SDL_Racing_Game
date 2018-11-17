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

class cTextureMgr
{
private:
	static cTextureMgr* pInstance;
	map<LPCSTR, cTexture*> textureList;
	SDL_Renderer* theSDLRenderer;

public:
	static cTextureMgr* getInstance();
	cTextureMgr();
	cTextureMgr(SDL_Renderer* theRenderer);
	~cTextureMgr();
	void addTexture(LPCSTR txtName, LPCSTR theFilename);
	cTexture* getTexture(LPCSTR textureName);		// return the texture.
	void setRenderer(SDL_Renderer* ptheRenderer); // Set the renderer
	void deleteTextures();						// Delete all textures;
	// Added this to allow scenes to delete the textures specific to them.
	void deleteTexture(LPCSTR txtName);			// Delete a single textures;
};
#endif