#include "Controller.h"
#include "InputChannel.h"
#include <iostream>

#include "cCamera.h"


Controller::Controller(int id)
{
	testControllerID = id;
	cam = nullptr;
}

void Controller::OnEvent(AbstractEvent e)
{
	std::cout << "Controller " << testControllerID << " Flag: " << e.flag << " x: " << e.value_x << " y: " << e.value_y << std::endl;
	
	if (cam)
	{
		SDL_Point pos = cam->GetPosition();
		pos.x += e.value_x;
		pos.y -= e.value_y;
		cam->SetPosition(pos);
	}
}
