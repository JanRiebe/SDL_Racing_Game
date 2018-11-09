#pragma once
#include "cTexture.h"
#include "GameConstants.h"

class cTileMap :
	public cTexture
{
private:
	//Defines what tile is placed where.
	Uint8 mapDefinition[MAP_WIDTH][MAP_HEIGHT];
	//Rows and rollums of the sprite sheet.
	int sheetRows;
	int sheetCollumns;
	SDL_Rect sourceRect;
	SDL_Rect destinationRect;
	//Updates sourceRect to fit the tile defined in mapDefinition. Parameter tileIndex is the index pointing to data in the map definition.
	SDL_Rect* findSourceRect(int tileIndex_x, int tileIndex_y);
	//Returns the destination rect for the position in the map definition. Parameter tileIndex is the index pointing to data in the map definition.
	SDL_Rect* findDestinationRect(int tileIndex_x, int tileIndex_y, SDL_Rect* wholeMapDest);

public:
	cTileMap();
	~cTileMap();

	//Renders this texture as a tile map.
	void renderMap(SDL_Renderer* theRenderer, SDL_Rect* theDestRect, FPoint theScaling);

	bool loadTexture(LPCSTR theFilename, SDL_Renderer *theRenderer, int rows, int collumns);

	//Loads the map definition.
	bool loadMap(LPCSTR theFilename);
};

//TODO Tile maps can just use normal textures.
//The map definition, findSourceRect and findDestinationRect could be part of the map sprite.
//This way different maps could use the same sprite sheet (which will probably be the same for different maps anyway).
//TODO change this class into a subclass of sprite cSpriteMap.