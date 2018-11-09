#include "cTileMap.h"



cTileMap::cTileMap()
{
}


cTileMap::~cTileMap()
{
}

void cTileMap::renderMap(SDL_Renderer * theRenderer, SDL_Rect * theDestRect, FPoint theScaling)
{
	for (int x = 0; x < MAP_WIDTH; ++x)
	{
		for (int y = 0; y < MAP_HEIGHT; ++y)
		{
			renderTexture(theRenderer, getTexture(), findSourceRect(x, y), findDestinationRect(x, y, theDestRect), theScaling);
		}
	}
}



bool cTileMap::loadTexture(LPCSTR theFilename, SDL_Renderer * theRenderer, int rows, int collumns)
{
	bool success = cTexture::loadTexture(theFilename, theRenderer);

	// Setting the tile rows and collumns.
	this->sheetCollumns = collumns;
	this->sheetRows = rows;	

	// Setting the width of the tiles.
	sourceRect.w = getTWidth() / collumns;
	sourceRect.h = getTHeight() / rows;
	
	return success;
}

bool cTileMap::loadMap(LPCSTR theFilename)
{
	//TODO load tile map definition from file

	//This is for testing purpose, filling the map with some stuff.
	for (int x = 0; x < MAP_WIDTH; ++x)
	{
		for (int y = 0; y < MAP_HEIGHT; ++y)
		{
			mapDefinition[x][y] = (x*y) % (sheetRows*sheetCollumns);
		}
	}


	return true;
}



SDL_Rect* cTileMap::findSourceRect(int tileIndex_x, int tileIndex_y)
{
	//Ensuring the tile index isn't larger than the length of the tile map definition.
	tileIndex_x = tileIndex_x % MAP_WIDTH;
	tileIndex_y = tileIndex_y % MAP_HEIGHT;

	// Calculating the position of the tile in the sprite sheet using the map definition,
	// the amount of tiles and the fixed width and height of a tile.
	sourceRect.x = sourceRect.w * (mapDefinition[tileIndex_x][tileIndex_y] % sheetCollumns);
	sourceRect.y = sourceRect.h * (mapDefinition[tileIndex_x][tileIndex_y] / sheetRows);

	return &sourceRect;
}

SDL_Rect * cTileMap::findDestinationRect(int tileIndex_x, int tileIndex_y, SDL_Rect * wholeMapDest)
{
	destinationRect.w = wholeMapDest->w / MAP_WIDTH;
	destinationRect.h = wholeMapDest->h / MAP_WIDTH;

	destinationRect.x = wholeMapDest->x + tileIndex_x*destinationRect.w;
	destinationRect.y = wholeMapDest->y + tileIndex_y*destinationRect.h;

	return &destinationRect;
}
