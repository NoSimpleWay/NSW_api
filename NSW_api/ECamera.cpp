#include "ECamera.h"
#include <NSW_api\EWindow.h>

float ECamera::get_world_position_x(ECamera* _camera)
{
	return (EWindow::mouse_x + _camera->position_x - EGraphicCore::SCR_WIDTH / 2.0f) / _camera->zoom ;
}

float ECamera::get_world_position_y(ECamera* _camera)
{
	return (EWindow::mouse_y + _camera->position_y - EGraphicCore::SCR_HEIGHT / 2.0f) / _camera->zoom;
}

ECamera::ECamera()
{
}

ECamera::~ECamera()
{
}
