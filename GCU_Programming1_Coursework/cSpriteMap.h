#pragma once
#include "cSpriteSheet.h"
#include "MapDefinition.h"

class cSpriteMap :
	public cSpriteSheet
{
private:
	//Layout of the tile map.
	MapDefinition mapDef;
	//Used to write a tile on a specific part of the whole sprite's position.
	SDL_Rect destinationRect;
	//Returns the destination rect for the position in the map definition. Parameter tileIndex is the index pointing to data in the map definition.
	SDL_Rect* findDestinationRect(int tileIndex_x, int tileIndex_y, SDL_Rect* wholeMapDest);
public:
	//Constructor. Parameter mapDefinition defines the layout in which this map should be rendered. Parameter sheetRows and sheetColumns specify how the texture should be sliced into tiles.
	cSpriteMap(int sheetRows = 1, int sheetColumns = 1);
	~cSpriteMap();
	// Renders this sprite based on the internal variables spritePos_2D, spriteScale and spriteRotationAngle. This should be overwritten by subclasses and used in general for rendering. 
	virtual void render(SDL_Renderer* theRenderer, cCamera* theCamera);
	//Renders this texture as a tile map.
	void render(SDL_Renderer* theRenderer, SDL_Rect* theDestRect, FPoint theScaling);
	void loadMap(string mapName);
	MapDefinition getMapDefinition();
	SDL_Rect getBoundingBox(int columns, int row);
};

