#pragma once
#include "EntityManager.h"
#include "NSW_api/EUtils.h"
#include "EPath.h"
#include "NSW_api/ETextureAtlas.h"
#include <NSW_api\EWindow.h>

std::vector <Entity*> Entity::entity_list;
ECluster* ECluster::clusters[CLUSTER_DIM][CLUSTER_DIM];


Entity::Entity()
{
	//already_updated = false;
	ESprite* sp = new ESprite();

	sprite_list.push_back(sp);
	sp->gabarite.push_back(ETextureAtlas::put_texture_to_atlas("data/sphere.png", EWindow::default_texture_atlas));

	sp->offset_x.push_back(-25.0f);
	sp->offset_y.push_back(0.0f);
}

Entity::~Entity()
{
}

void Entity::draw_sprite(Batcher* _b, float _d)
{
	int sprite_id = 0;
	EGabarite* link;

	for (ESprite* spr : sprite_list)
	{
		if (*spr->rotate_by_move)
		if (*speed_x * *speed_x > *speed_y * *speed_y)
		{
			if (*speed_x > 0) { sprite_id = 1; }
			else { sprite_id = 3; }
		}
		else
		{
			if (*speed_y > 0) { sprite_id = 0; }
			else { sprite_id = 2; }
		}

		//link = spr->gabarite.at(sprite_id);

		_b->draw_gabarite
		(
			*position_x + spr->offset_x.at(sprite_id),
			*position_y + spr->offset_y.at(sprite_id),

			spr->gabarite.at(sprite_id)->size_x,
			spr->gabarite.at(sprite_id)->size_y,

			spr->gabarite.at(sprite_id)
		);
	}
}

bool ECluster::collision_left(Entity* _a, Entity* _b)
{
	float pseudo_line = *_b->position_x - *_b->collision_left - *_a->collision_right;

	if
	(
		(*_a->position_x < pseudo_line)
		&&
		(*_a->position_x + *_a->real_speed_x >= pseudo_line)
		&&
		(*_a->position_y + *_a->real_speed_y / *_a->real_speed_x * (pseudo_line  - *_a->position_x) <= *_b->position_y + *_a->collision_up + *_b->collision_down)
		&&
		(*_a->position_y + *_a->real_speed_y / *_a->real_speed_x * (pseudo_line - *_a->position_x) >= *_b->position_y - *_a->collision_down - *_b->collision_up)
	)
	{ 
	return true;
	}

	return false;
}

bool ECluster::collision_right(Entity* _a, Entity* _b)
{
	float pseudo_line = *_b->position_x + *_b->collision_right + *_a->collision_left;

	if
	(
		(*_a->position_x > pseudo_line)
		&&
		(*_a->position_x + *_a->real_speed_x <= pseudo_line)
		&&
		(*_a->position_y + *_a->real_speed_y / *_a->real_speed_x * ( *_a->position_x - pseudo_line) <= *_b->position_y + *_a->collision_up + *_b->collision_down)
		&&
		(*_a->position_y + *_a->real_speed_y / *_a->real_speed_x * (*_a->position_x - pseudo_line) >= *_b->position_y - *_a->collision_down - *_b->collision_up)
	)
	{ 
	return true;
	}

	return false;
}

bool ECluster::collision_up(Entity* _a, Entity* _b)
{
	float pseudo_line = *_b->position_y + *_b->collision_up + *_a->collision_down;

	if
	(
		(*_a->position_y > pseudo_line)
		&&
		(*_a->position_y + *_a->real_speed_y <= pseudo_line)
		&&
		(*_a->position_x + *_a->real_speed_x / *_a->real_speed_y * ( pseudo_line - *_a->position_y ) <= *_b->position_x + *_a->collision_right + *_b->collision_left)
		&&
		(*_a->position_x + *_a->real_speed_x / *_a->real_speed_y * ( pseudo_line  - *_a->position_y ) >= *_b->position_x - *_a->collision_left - *_b->collision_right)
	)
	{ 
		return true;
	}

	return false;
}

bool ECluster::collision_down(Entity* _a, Entity* _b)
{
	float pseudo_line = *_b->position_y - *_b->collision_down - *_a->collision_up;

	if
	(
		(*_a->position_y < pseudo_line)
		&&
		(*_a->position_y + *_a->real_speed_y >= pseudo_line)
		&&
		(*_a->position_x + *_a->real_speed_x / *_a->real_speed_y * ( *_a->position_y - pseudo_line) <= *_b->position_x + *_a->collision_right + +*_b->collision_left)
		&&
		(*_a->position_x + *_a->real_speed_x / *_a->real_speed_y * ( *_a->position_y - pseudo_line) >= *_b->position_x - *_a->collision_left - *_b->collision_right)
	)
	{ 
		return true;
	}

	return false;
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

	int path_x = EMath::clamp_value_int((int)(_x / EPath::PATH_SIZE), 0, EPath::PATH_DIM);
	int path_y = EMath::clamp_value_int((int)(_y / EPath::PATH_SIZE), 0, EPath::PATH_DIM);

	//EPath::block[path_x][path_y] += EPath::ENTITY_BLOCK_VALUE;
}

