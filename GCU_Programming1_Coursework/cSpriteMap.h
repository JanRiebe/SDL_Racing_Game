#pragma once
#include "cSpriteSheet.h"
#include "MapDefinition.h"

class cSpriteMap :
	public cSpriteSheet
{
private:
	//TODO should this be a pointer. Who should have ownership over map definitions?
	MapDefinition mapDef;
	SDL_Rect destinationRect;
	//Returns the destination rect for the position in the map definition. Parameter tileIndex is the index pointing to data in the map definition.
	SDL_Rect* findDestinationRect(int tileIndex_x, int tileIndex_y, SDL_Rect* wholeMapDest);
public:
	//Constructor. Parameter mapDefinition defines the layout in which this map should be rendered. Parameter sheetRows and sheetColumns specify how the texture should be sliced into tiles.
	cSpriteMap(int sheetRows = 1, int sheetColumns = 1);
	~cSpriteMap();
	//Renders this texture as a tile map.
	void render(SDL_Renderer* theRenderer, SDL_Rect* theDestRect, FPoint theScaling);
	void loadMap(string mapName);
};

