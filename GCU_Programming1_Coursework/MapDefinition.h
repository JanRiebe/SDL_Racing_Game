#pragma once
#include "GameConstants.h"

struct MapDefinition
{
	// Defines what tile is placed where.
	Uint8 tiles[MAP_WIDTH][MAP_HEIGHT];
	// Defines whether a whole tile acts as a collider.
	bool impassable[MAP_WIDTH][MAP_HEIGHT];
};