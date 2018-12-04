#include "cSpriteMap.h"
#include <iostream>
#include <fstream>


cSpriteMap::cSpriteMap(int sheetRows, int sheetColumns): cSpriteSheet(sheetRows, sheetColumns)
{
}


cSpriteMap::~cSpriteMap()
{
}

void cSpriteMap::render(SDL_Renderer * theRenderer, cCamera * theCamera)
{
	for (int x = 0; x < MAP_WIDTH; ++x)
	{
		for (int y = 0; y < MAP_HEIGHT; ++y)
		{
			cSpriteSheet::render(theRenderer, mapDef.tiles[x][y], findDestinationRect(x, y, &theCamera->WorldToScreen(transform)), spriteScale);
		}
	}
}

void cSpriteMap::render(SDL_Renderer * theRenderer, SDL_Rect * theDestRect, FPoint theScaling)
{
	for (int x = 0; x < MAP_WIDTH; ++x)
	{
		for (int y = 0; y < MAP_HEIGHT; ++y)
		{
			cSpriteSheet::render(theRenderer, mapDef.tiles[x][y], findDestinationRect(x, y, theDestRect), theScaling);
		}
	}
}

void cSpriteMap::loadMap(string mapName)
{
	

	// Clean old map definition
	for (int x = 0; x < MAP_WIDTH; ++x)
	{
		for (int y = 0; y < MAP_HEIGHT; ++y)
		{
			mapDef.tiles[x][y] = 0;
			mapDef.impassable[x][y] = false;
		}
	}


	string path = "Data\\" + mapName + ".dat";
	ifstream file;
		
	file.open(path, ios::binary);
	if (!file.is_open())
	{
		cout << "Error opening file " << mapName <<".dat" << endl;
	}
	
	int x = 0;
	int y = 0;
	while (!file.eof() && x < MAP_WIDTH && y < MAP_HEIGHT) {
		// Reading in the raw tile definition
		file >> mapDef.tiles[x][y];

		// Processing the tile definition
		// The last part of the number indicates whether the tile is passable, 0 = impassable 1 = passable
		mapDef.impassable[x][y] = 1 - mapDef.tiles[x][y] % 2;
		// Removing the last part of the number.
		mapDef.tiles[x][y] = mapDef.tiles[x][y] / 10;

		x++;
		if (x == MAP_WIDTH)
		{
			x = 0;
			y++;
		}
	}
	file.close();
	cout << x << " " << y << endl;

	cout << "Successfully loaded map file " << mapName << ".map" << endl;

}

MapDefinition cSpriteMap::getMapDefinition()
{
	return mapDef;
}

SDL_Rect cSpriteMap::getBoundingBox(int column, int row)
{
	// Get the bounding box for the tile at columns, row.
	return *(findDestinationRect(column, row, &transform));
}



SDL_Rect * cSpriteMap::findDestinationRect(int tileIndex_x, int tileIndex_y, SDL_Rect * wholeMapDest)
{
	int whole_w, whole_h, whole_x, whole_y;
	if (wholeMapDest)
	{
		whole_w = wholeMapDest->w;
		whole_h = wholeMapDest->h;
		whole_x = wholeMapDest->x;
		whole_y = wholeMapDest->y;
	}
	else
	{
		whole_w = transform.w;
		whole_h = transform.h;
		whole_x = transform.x;
		whole_y = transform.y;
	}
		
	destinationRect.w = whole_w / MAP_WIDTH;
	destinationRect.h = whole_h / MAP_WIDTH;

	destinationRect.x = whole_x + tileIndex_x*destinationRect.w;
	destinationRect.y = whole_y + tileIndex_y*destinationRect.h;

	return &destinationRect;
}
