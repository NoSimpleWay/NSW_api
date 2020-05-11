#pragma once
class ECamera
{
public:
	float position_x;
	float position_y;

	float speed_x;
	float speed_y;

	float zoom = 1.0f;

	static float get_world_position_x(ECamera* _camera);
	static float get_world_position_y(ECamera* _camera);

	ECamera();
	~ECamera();
};