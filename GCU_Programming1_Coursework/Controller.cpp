#include "Controller.h"
#include "InputChannel.h"
#include <iostream>




Controller::Controller(int id)
{
	testControllerID = id;
}

void Controller::OnEvent(AbstractEvent e)
{
	std::cout << "Controller " << testControllerID << " Flag: " << e.flag << " x: " << e.value_x << " y: " << e.value_y << std::endl;
}
