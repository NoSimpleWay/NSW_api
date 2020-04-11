#pragma once
#include <vector>


class ECluster;

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


class ECluster
{
public:
	ECluster();
	~ECluster();

	std::vector<Entity*> entity_list;
	

	//----------STATIC----------------------------
	static const int CLUSTER_SIZE = 250;
	static const int CLUSTER_DIM = 30;

	static void put_entity(Entity* _e, float _x, float _y);

	static ECluster* clusters[CLUSTER_DIM][CLUSTER_DIM];
};