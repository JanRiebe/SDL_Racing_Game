/*
=================
cTextureMgr.cpp
- CPP file for class definition - IMPLEMENTATION
- CPP file for the TextureMgr class
=================
*/
#include "cTextureMgr.h"
cTextureMgr* cTextureMgr::pInstance = NULL;

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cTextureMgr* cTextureMgr::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cTextureMgr();
	}
	return cTextureMgr::pInstance;
}

/*
=================
- Data constructor initializes the TextureMgr object 
- Is always called, thus ensures all TextureMgr objects are in a consistent state.
=================
*/
cTextureMgr::cTextureMgr()
{
	
}

cTextureMgr::cTextureMgr(SDL_Renderer* theRenderer)
{
	theSDLRenderer = theRenderer;
}

/*
=================
- Destructor.
=================
*/
cTextureMgr::~cTextureMgr()
{
	
}




/*
=================
- add the texture as an animated texture.
=================
*/
void cTextureMgr::addTextureAnimated(LPCSTR txtName, LPCSTR theFilename, int rows, int collums)
{
	if (!getTextureAnimated(txtName))
	{
		cTextureAnimated * newTxt = new cTextureAnimated();
		newTxt->loadTexture(theFilename, theSDLRenderer, rows, collums);
		//Adding the animated texture both to the textureList and the animatedTextureList
		//so that it can be accessed through both getTexture and getTextureAnimated.
		textureList.insert(make_pair(txtName, newTxt));
		animatedTextureList.insert(make_pair(txtName, newTxt));
	}
}


void cTextureMgr::addTexture(LPCSTR txtName, LPCSTR theFilename)
{
	if (!getTexture(txtName))
	{
		cTexture * newTxt = new cTexture();
		newTxt->loadTexture(theFilename, theSDLRenderer);
		textureList.insert(make_pair(txtName, newTxt));
	}
}

void cTextureMgr::deleteTextures()
{
	for (map<LPCSTR, cTexture*>::iterator txt = textureList.begin(); txt != textureList.end(); ++txt)
	{
		delete txt->second;
	}
}


/*
=================
- return the texture.
=================
*/
cTexture* cTextureMgr::getTexture(LPCSTR textureName)        // return the texture.
{
	map<LPCSTR, cTexture*>::iterator txt = textureList.find(textureName);
	if (txt != textureList.end())
	{
		return txt->second;
	}
	else
	{
		return NULL;
	}
}

/*
=================
- return the texture as an animated texture.
=================
*/
cTextureAnimated * cTextureMgr::getTextureAnimated(LPCSTR textureName)
{
	map<LPCSTR, cTextureAnimated*>::iterator txt = animatedTextureList.find(textureName);
	if (txt != animatedTextureList.end())
	{
		return txt->second;
	}
	else
	{
		return NULL;
	}
}


/*
=================
- Set the renderer.
=================
*/
void cTextureMgr::setRenderer(SDL_Renderer* ptheRenderer)
{
	this->theSDLRenderer = ptheRenderer;
}