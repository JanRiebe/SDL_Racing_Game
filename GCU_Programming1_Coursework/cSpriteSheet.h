#pragma once
#include "cSprite.h"
class cSpriteSheet :
	public cSprite
{
private:
	//The amount of rows and columns the texture should be divided into.
	int columns;
	int rows;
	//The rect that defines which part of the texture should be rendered.
	SDL_Rect sourceRect;
	//Updates sourceRect according to the index. Returns a pointer to sourceRect.
	SDL_Rect* findSourceRect(int index);

public:
	//Render a tile from the sprite sheet, indext by sheetIndex.
	void render(SDL_Renderer* theRenderer, int sheetIndex, SDL_Rect* theDestRect, FPoint theScaling);
	//Render a tile from the sprite sheet, indext by sheetIndex. Allows rotating.
	void render(SDL_Renderer* theRenderer, int sheetIndex, SDL_Rect* theDestRect, double rotAngle, SDL_Point* spriteCentre, FPoint theScaling);
	//Constructor. Parameter sheetRows and sheetColumns specify how the texture should be sliced into tiles.
	cSpriteSheet(int sheetRows = 1, int sheetColumns = 1);
	~cSpriteSheet();
	int getSheetRows();
	int getSheetColumns();
	void setSheetGrid(int sheetRows, int sheetColumns);
};

