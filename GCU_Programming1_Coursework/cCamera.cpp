#include "cCamera.h"
#include "GameConstants.h"
#include "gameHeaders.h"


cCamera::cCamera()
{
	pos = { 0,0 };
	viewport.x = 0;
	viewport.y = 1;
	viewport.w = WINDOW_WIDTH;
	viewport.h = WINDOW_HEIGHT;
	cout << "Camera created with basic viewport " << viewport.w << " " << viewport.h << endl;
}


cCamera::~cCamera()
{
}

void cCamera::SetViewport(SDL_Rect v)
{
	cout << "Viewport assigned to camera "<< v.w << " " << v.h << endl;
	viewport = v;
}

void cCamera::SetPosition(SDL_Point position)
{
	pos = position;
}

SDL_Point cCamera::GetPosition()
{
	return pos;
}

SDL_Rect cCamera::GetViewport()
{
	return viewport;
}

SDL_Rect cCamera::WorldToScreen(SDL_Rect worldPos)
{
	worldPos.x -= pos.x;
	worldPos.y -= pos.y;
	return worldPos;
}
