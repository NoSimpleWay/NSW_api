#pragma once
#include "EntityManager.h"
#include "NSW_api/EUtils.h"

std::vector <Entity*> Entity::entity_list;
ECluster* ECluster::clusters[CLUSTER_DIM][CLUSTER_DIM];


Entity::Entity()
{
}

Entity::~Entity()
{
}

ECluster::ECluster()
{
}

ECluster::~ECluster()
{
}


void ECluster::put_entity(Entity* _e, float _x, float _y)
{
	*_e->position_x = _x;
	*_e->position_y = _y;

	int cluster_x =  EMath::clamp_value_int((int)(_x / CLUSTER_SIZE), 0, CLUSTER_DIM);
	int cluster_y =  EMath::clamp_value_int((int)(_y / CLUSTER_SIZE), 0, CLUSTER_DIM);
	clusters[cluster_x][cluster_y]->entity_list.push_back(_e);
}
