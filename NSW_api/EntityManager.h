#pragma once
#include <vector>
#include "NSW_api/EGabarite.h"
#include "NSW_api/Batcher.h"
class ECluster;
class ESprite;

class Entity
{
public:
	float* position_x = new float();
	float* position_y = new float();

	float* speed_x = new float();
	float* speed_y = new float();

	float* real_speed_x = new float();
	float* real_speed_y = new float();

	float* mass = new float(10.0f);

	float* collision_up = new float(12.0f);
	float* collision_down = new float(12.0f);
	float* collision_left = new float(25.0f);
	float* collision_right = new float(25.0f);

	bool* already_updated = new bool(false);

	bool* need_change_cluster = new bool(false);

	Entity();
	~Entity();

	static std::vector<Entity*> entity_list;


	std::vector <EGabarite*> body;
	std::vector <float> body_offset_x;
	std::vector <float> body_offset_y;

	bool body_rotate_by_move = false;

	bool controlled_by_ai = true;
	bool controlled_by_player = false;

	std::vector<ESprite*> sprite_list;

	void draw_sprite(Batcher* _b, float _d);

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

	bool static collision_left(Entity* _a, Entity* _b);
	bool static collision_right(Entity* _a, Entity* _b);
	bool static collision_down(Entity* _a, Entity* _b);
	bool static collision_up(Entity* _a, Entity* _b);
};

class ESprite
{
public:
	std::vector<EGabarite*> gabarite;

	std::vector<float> offset_x;
	std::vector<float> offset_y;

	bool* rotate_by_move = new bool(false);
	bool* rotate_by_target = new bool(false);
};