#pragma once
#include <vector>
class Entity
{
public:
	float* position_x = new float();
	float* position_y = new float();

	float* speed_x = new float();
	float* speed_y = new float();

	Entity();
	~Entity();

	static std::vector<Entity*> entity_list;

};