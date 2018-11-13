#include "cCamera.h"



cCamera::cCamera()
{
}


cCamera::~cCamera()
{
}

void cCamera::SetPosition(SDL_Point position)
{
	pos = position;
}

SDL_Point cCamera::GetPosition()
{
	return pos;
}

SDL_Rect cCamera::WorldToScreen(SDL_Rect worldPos)
{
	worldPos.x -= pos.x;
	worldPos.y -= pos.y;
	return worldPos;
}
