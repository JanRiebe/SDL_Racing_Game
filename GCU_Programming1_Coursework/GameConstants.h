#ifndef _GAMECONSTANTS_H
#define _GAMECONSTANTS_H

// Windows & SDL 
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib>

using namespace std::chrono;

#include <SDL.h>
// Image Texture loading library
#include <SDL_image.h>
// Font loading library
#include <SDL_ttf.h>
// Sound loading library
#include <SDL_mixer.h>

// Maths functions
#include <math.h>
constexpr auto PI = 3.14159265;

// STL Container & Algorithms
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

//Define the string to appear in the top left corner of the window
#define WINDOW_TITLE "Jans fun and educational racing game!"
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512

//Define the dimensions for tile maps
const int MAP_WIDTH = 64;
const int MAP_HEIGHT = 64;

//The maximum number of players
const int MAX_PLAYERS = 4;

// This header file contains all the constants & enumarated types for the game
typedef struct fpoint
{
	float  X;
	float  Y;

	// Overloading + operator for fpoint,
	// to allow shorthand vector addition in physics simulation.
	fpoint operator+(fpoint const &rhs)
	{
		fpoint result;
		result.X = X + rhs.X;
		result.Y = Y + rhs.Y;
		return result;
	}

	// Overloading - operator for fpoint,
	// to allow shorthand negation in physics simulation.
	fpoint operator-()
	{
		fpoint result;
		result.X = -X;
		result.Y = -Y;
		return result;
	}

	// Overloading - operator for fpoint,
	// to allow shorthand vector subtraction in physics simulation.
	fpoint operator-(fpoint const &rhs)
	{
		fpoint result;
		result.X = X - rhs.X;
		result.Y = Y - rhs.Y;
		return result;
	}

	// Overloading += operator for fpoint,
	// to allow shorthand vector addition in physics simulation.
	fpoint operator+=(fpoint const &other)
	{
		X += other.X;
		Y += other.Y;
		return *this;
	}
	// Overloading -= operator for fpoint,
	// to allow shorthand vector subtraction in physics simulation.
	fpoint operator-=(fpoint const &other)
	{
		X -= other.X;
		Y -= other.Y;
		return *this;
	}

	// Overloading / operator for float values,
	// to allow shorthand vector scalar division in physics simpulation.
	fpoint operator/(float const &f)
	{
		fpoint n;
		n.X = this->X / f;
		n.Y = this->Y / f;
		return n;
	}

	// Overloading * operator for float values,
	// to allow shorthand vector scalar multiplication in physics simpulation.
	fpoint operator*(float const &f)
	{
		fpoint n;
		n.X = this->X * f;
		n.Y = this->Y * f;
		return n;
	}

	// Calculates the length of the vector this point represents.
	float length()
	{
		return sqrt(X*X + Y*Y);
	}

	// Returns the dot product.
	float dotProduct(fpoint* other)
	{
		return X*other->X + Y*other->Y;
	}

}FPoint;

inline SDL_Point operator+(SDL_Point const &a, SDL_Point const &b)
{
	return SDL_Point{ a.x + b.x , a.y + b.y };
}

enum class soundType { sfx, music };
enum class textType { solid, blended, shaded };


// Messages that are passed between colliders on collision.
enum CollisionMessage
{
	COLLISION,
	TRIGGER,
	SAFEHOUSE
};



enum Teams
{
	POLICE,
	CRIMINALS,
	NUMBER_OF_TEAMS
};


#endif