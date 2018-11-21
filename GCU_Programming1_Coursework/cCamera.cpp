#include "cCamera.h"
#include "GameConstants.h"
#include "gameHeaders.h"


cCamera::cCamera()
{
	pos = { 0,0 };
	viewport.x = 0;
	viewport.y = 0;
	SetViewport({0,0, WINDOW_WIDTH, WINDOW_HEIGHT });

	target = NULL;
}


cCamera::~cCamera()
{
}

void cCamera::SetViewport(SDL_Rect v)
{
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

SDL_Point cCamera::WorldToScreen(SDL_Point worldPos)
{
	worldPos.x -= pos.x;
	worldPos.y -= pos.y;
	return worldPos;
}

void cCamera::update(double deltaTime)
{
	// If a target has been set for this camera
	if (target)
	{
		// move the camera position to the target position.
		pos.x = target->getPosition().x + offset.x;
		pos.y = target->getPosition().y + offset.y;
	}
}

void cCamera::setTarget(cSprite * t)
{
	target = t;
	offset.x = (t->getSpriteDimensions().w - viewport.w) / 2;
	offset.y = (t->getSpriteDimensions().h - viewport.h) / 2;
}
