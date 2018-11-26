#include "cSpriteSheet.h"
#include "gameHeaders.h"


SDL_Rect * cSpriteSheet::findSourceRect(int index)
{
	sourceRect.x = sourceRect.w * (index % columns);
	sourceRect.y = sourceRect.h * (index / columns);

	return &sourceRect;
}


void cSpriteSheet::render(SDL_Renderer * theRenderer, int sheetIndex, SDL_Rect * theDestRect, FPoint theScaling)
{
	cSprite::render(theRenderer, findSourceRect(sheetIndex), theDestRect, theScaling);
}

void cSpriteSheet::render(SDL_Renderer * theRenderer, int sheetIndex, SDL_Rect * theDestRect, double rotAngle, SDL_Point * spriteCentre, FPoint theScaling)
{
	cSprite::render(theRenderer, findSourceRect(sheetIndex), theDestRect, rotAngle, spriteCentre, theScaling);
}



cSpriteSheet::cSpriteSheet(int sheetColumns, int sheetRows):rows(sheetRows), columns(sheetColumns), cSprite()
{
}

cSpriteSheet::~cSpriteSheet()
{
}

int cSpriteSheet::getSheetRows()
{
	return rows;
}

int cSpriteSheet::getSheetColumns()
{
	return columns;
}

void cSpriteSheet::setSheetGrid(int sheetColumns, int sheetRows)
{
	rows = sheetRows;
	columns = sheetColumns;

	//Set width and height of source rect that will be used to cut out the tile to render.
	sourceRect.w = textureDimension.w / columns;
	sourceRect.h = textureDimension.h / rows;
}

void cSpriteSheet::setSpriteScale(FPoint sScale)
{
	// Changing sScale depending on the sheet grid size,
	sScale.X /= columns;
	sScale.Y /= rows;
	
	// then callling the base class function.
	cSprite::setSpriteScale(sScale);
}
