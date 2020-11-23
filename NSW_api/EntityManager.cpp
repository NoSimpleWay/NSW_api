#pragma once
#include "EntityManager.h"
#include "NSW_api/EUtils.h"
#include "EPath.h"
#include "NSW_api/ETextureAtlas.h"
#include <NSW_api\EWindow.h>
#include "EWindowEditor.h"

std::vector <Entity*> Entity::entity_list;
std::vector <Entity*> Entity::entity_collection_list;

ECluster* ECluster::clusters[CLUSTER_DIM][CLUSTER_DIM];

std::vector<Entity::HIT_ACTION> Entity::HIT_ACTIONS_LIST;
std::vector<std::string> Entity::HIT_ACTION_NAME_LIST;

bool Entity::is_collision_down;
bool Entity::is_collision_left;
bool Entity::is_collision_right;
bool Entity::is_collision_up;
int Entity::dolboyob = 0;

std::vector <int> Entity::entity_attribute_id
=
{
	EAttr::EA_LIFE,
	EAttr::EA_SHIELD,
	EAttr::ENTITY_ATTRIBUTE_SHIELD_REGEN,
	EAttr::ENTITY_ATTRIBUTE_SHIELD_OVERLOAD_CAPACITY,
	EAttr::ENTITY_ATTRIBUTE_SHIELD_OVERLOAD_DURATION,
	EAttr::ENTITY_ATTRIBUTE_MASS,
	EAttr::ENTITY_ATTRIBUTE_SPEED,
	EAttr::ENTITY_ATTRIBUTE_DRAG,

	EAttr::ENTITY_ATTRIBUTE_SHADOW_TALL,

	EAttr::ENTITY_ATTRIBUTE_LIGHT_SOURCE_RED,
	EAttr::ENTITY_ATTRIBUTE_LIGHT_SOURCE_GREEN,
	EAttr::ENTITY_ATTRIBUTE_LIGHT_SOURCE_BLUE
};

std::vector < std::string > Entity::entity_attribute_names
=
{
	"Life",
	"Shield",
	"Shield regen",
	"Overload capacity",
	"Overload duration",
	"Mass",
	"Speed",
	"Drag",

	"Shadow tall",

	"Lightsoucre red",
	"Lightsoucre green",
	"Lightsoucre blue"
};

std::vector <int> Entity::entity_bool_attribute_id
=
{
	EntityBoolAttributes::ENTITY_BOOL_ATTRIBUTE_INMOVABLE,
	EntityBoolAttributes::ENTITY_BOOL_CONTROLLED_BY_AI,
	EntityBoolAttributes::ENTITY_BOOL_CONTROLLED_BY_PLAYER,
	EntityBoolAttributes::ENTITY_BOOL_HAVE_LIGHT_SOURCE,
	EntityBoolAttributes::ENTITY_BOOL_GHOST,
	EntityBoolAttributes::ENTITY_BOOL_NO_PATH_BLOCK,
	EntityBoolAttributes::ENTITY_BOOL_NO_LIGHT_BLOCK

};

std::vector < std::string > Entity::entity_bool_attribute_names
=
{
	"Inmovable",
	"Controlled by AI",
	"Controlled by Player",
	"Light Source",
	"Ghost",
	"No path block",
	"No light block"


};

void Entity::test_hit_action_destroy_touch(Entity* _a, Entity* _b, int _side)
{
	*_b->need_remove = true;
}

void Entity::test_hit_action_self_destroy_on_hit(Entity* _a, Entity* _b, int _side)
{
	*_a->need_remove = true;
}

int Entity::search_hit_action(std::string _text)
{
	for (int i = 0; i < HIT_ACTION_NAME_LIST.size(); i++)
	{
		if (HIT_ACTION_NAME_LIST.at(i) == _text)
		{
			return i;
		}
	}
	return -1;
}

std::string Entity::get_hit_action_name(HIT_ACTION _action)
{
	for (int i = 0; i < HIT_ACTIONS_LIST.size(); i++)
	{
		if (HIT_ACTIONS_LIST.at(i) == _action)
		{
			return HIT_ACTION_NAME_LIST.at(i);
		}
	}

	return "";
}

/*int Entity::get_hit_action_name(HIT_ACTION* _action)
{

	return 0;
}*/

void Entity::collision_process(Entity* _e, float _d)
{
	bool collision_left = *_e->already_moved_x;
	bool collision_right = *_e->already_moved_x;
	bool collision_up = *_e->already_moved_y;
	bool collision_down = *_e->already_moved_y;



	*_e->already_updated = true;

	*_e->prev_cluster_x = (int)(*_e->position_x / ECluster::CLUSTER_SIZE);
	*_e->prev_cluster_y = (int)(*_e->position_y / ECluster::CLUSTER_SIZE);

	Entity* nearest_entity_left_side = NULL;
	Entity* nearest_entity_right_side = NULL;
	Entity* nearest_entity_up_side = NULL;
	Entity* nearest_entity_down_side = NULL;

	float nearest_dist_left_side = 99999.0f;
	float nearest_dist_right_side = 99999.0f;
	float nearest_dist_up_side = 99999.0f;
	float nearest_dist_down_side = 99999.0f;


	////////////////////////////////////////////////////////////////////////////////////////////////////////

	*_e->target_vector_x = *_e->real_speed_x;
	*_e->target_vector_y = *_e->real_speed_y;

	int start_cluster_x = int(*_e->position_x / ECluster::CLUSTER_SIZE);
	int start_cluster_y = int(*_e->position_y / ECluster::CLUSTER_SIZE);
	if (*_e->real_speed_x > 0) { start_cluster_x -= 3; }
	else { start_cluster_x += 3; }
	if (*_e->real_speed_y > 0) { start_cluster_y -= 3; }
	else { start_cluster_y += 3; }
	//if (*e->real_speed_y > 0) { start_cluster_y -= 3; } else { start_cluster_y += 3; }

	int end_cluster_x = int((*_e->position_x + *_e->real_speed_x) / ECluster::CLUSTER_SIZE);
	int end_cluster_y = int((*_e->position_y + *_e->real_speed_y) / ECluster::CLUSTER_SIZE);
	if (*_e->real_speed_x > 0) { end_cluster_x += 3; }
	else { end_cluster_x -= 3; }
	if (*_e->real_speed_y > 0) { end_cluster_y += 3; }
	else { end_cluster_y -= 3; }


	int cluster_length_x = end_cluster_x - start_cluster_x;
	int cluster_length_y = end_cluster_y - start_cluster_y;

	int direction_x = 1;
	int direction_y = 1;

	if (cluster_length_x < 0) { direction_x = -1; }
	if (cluster_length_y < 0) { direction_y = -1; }

	int progress_x = 0;
	int progress_y = 0;


	for (int cx = start_cluster_x; cx != end_cluster_x + direction_x; cx += direction_x)
	{
		float projection_x = start_cluster_x;
		float projection_y = start_cluster_y;

		if (cluster_length_x != 0)
		{
			projection_x = cx;
			projection_y = start_cluster_y + cluster_length_y * progress_x / abs(cluster_length_x);
		}


		progress_y = 0;

		for (int cy = start_cluster_y; cy != end_cluster_y + direction_y; cy += direction_y)
			if
				(
				(cx >= 0) && (cy >= 0) && (cx < ECluster::CLUSTER_DIM) && (cy < ECluster::CLUSTER_DIM)
					&
					(
					(abs(projection_y - cy) <= 3)
						||
						(
						(progress_x <= 7) & (progress_y <= 7)
							)
						||
						(
						(progress_x >= abs(cluster_length_x) - 7) & (progress_y >= abs(cluster_length_y) - 7)
							)
						)
					)
			{
				if ((*_e->controlled_by_player) & ((EWindow::window_editor->is_active)||(false)) & (false))
				{
					if (abs(projection_y - cy) <= 3)
					{
						EGraphicCore::batch->setcolor(EColor::COLOR_PINK);
					}
					else
					{
						EGraphicCore::batch->setcolor_lum(EColor::COLOR_PINK, 0.55f);
					}
					EGraphicCore::batch->draw_gabarite(cx * ECluster::CLUSTER_SIZE, cy * ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, EGraphicCore::gabarite_white_pixel);


					EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
					EGraphicCore::batch->draw_gabarite(projection_x * ECluster::CLUSTER_SIZE, projection_y * ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, EGraphicCore::gabarite_white_pixel);
				}

				float cadist = 0.0f;
				if (!*_e->already_moved_x)
				{


					//left_side
					if (*_e->real_speed_x > 0)
					{
						for (Entity* e2 : ECluster::clusters[cx][cy]->entity_list)
							if ((_e != e2) & (!(*_e->is_bullet & *e2->is_bullet)) & (!*e2->is_ghost))
							{
								if (ECluster::collision_left(_e, e2))
								{
									cadist = *e2->position_x - *e2->collision_left - *_e->position_x;
									if (cadist < nearest_dist_left_side)
									{
										nearest_dist_left_side = cadist;
										nearest_entity_left_side = e2;
										//EWindow::window_editor->selected_entity = nearest_entity_left_side;
									}
									collision_left = true;
								}
							}
					}

					//right_side
					if (*_e->real_speed_x < 0)
					{

						for (Entity* e2 : ECluster::clusters[cx][cy]->entity_list)
							if ((_e != e2) & (!(*_e->is_bullet & *e2->is_bullet)) & (!*e2->is_ghost))
							{
								if (ECluster::collision_right(_e, e2))
								{
									cadist = *_e->position_x - *e2->position_x - *e2->collision_right;
									if (cadist < nearest_dist_right_side)
									{
										nearest_dist_right_side = cadist;
										nearest_entity_right_side = e2;
									}

									collision_right = true;
								}
							}
					}
				}

				if (!*_e->already_moved_y)
				{
					//up_side
					if (*_e->real_speed_y < 0)
					{
						for (Entity* e2 : ECluster::clusters[cx][cy]->entity_list)
							if ((_e != e2) & (!(*_e->is_bullet & *e2->is_bullet)) & (!*e2->is_ghost))
							{
								if (ECluster::collision_up(_e, e2))
								{
									cadist = *_e->position_y - *e2->position_y - *e2->collision_up;

									if (cadist < nearest_dist_up_side)
									{
										nearest_dist_up_side = cadist;
										nearest_entity_up_side = e2;
									}

									collision_up = true;
								}
							}
					}

					//down_side
					if (*_e->real_speed_y > 0)
					{
						for (Entity* e2 : ECluster::clusters[cx][cy]->entity_list)
							if ((_e != e2) & (!(*_e->is_bullet & *e2->is_bullet)) & (!*e2->is_ghost))
							{
								if (ECluster::collision_down(_e, e2))
								{
									cadist = *e2->position_y - *_e->position_y - *e2->collision_down;

									if (cadist < nearest_dist_down_side)
									{
										nearest_dist_down_side = cadist;
										nearest_entity_down_side = e2;
									}
									collision_down = true;
								}
							}
					}
				}

				progress_y++;
			}
			else
			{
				progress_y++;
			}

		progress_x++;
	}


	float total_impulse = 0;
	float total_mass = 0;
	float transfer_multiplier = 0;
	float speed_diff = 0;

	float delta = 0;
	//end of collision detect
	if (nearest_entity_left_side != NULL)
	{
		*_e->position_x = *nearest_entity_left_side->position_x - *nearest_entity_left_side->collision_left - *_e->collision_right;
	}

	{

		//if (*e->real_speed_x * *e->real_speed_x < 0.05f) { *e->real_speed_x = 0.0f; }
		//if (*e->real_speed_y * *e->real_speed_y < 0.05f) { *e->real_speed_y = 0.0f; }

		if ((!collision_left) & (!collision_right) & (!*_e->already_moved_x))
		{
			*_e->position_x += *_e->real_speed_x;
			*_e->already_moved_x = true;

			*_e->position_x = EMath::clamp_value_float(*_e->position_x, 1.0f, ECluster::CLUSTER_SIZE * ECluster::CLUSTER_DIM);

		}

		if ((!collision_up) & (!collision_down) & (!*_e->already_moved_y))
		{
			*_e->position_y += *_e->real_speed_y;
			*_e->already_moved_y = true;

			*_e->position_y = EMath::clamp_value_float(*_e->position_y, 1.0f, ECluster::CLUSTER_SIZE * ECluster::CLUSTER_DIM);
		}
	}

	if (nearest_entity_left_side != NULL)
	{
		if (*_e->real_speed_x > * nearest_entity_left_side->real_speed_x)
		{
			*_e->speed_y *= pow(0.1, _d);

			if (*nearest_entity_left_side->inmovable) { *_e->speed_x *= 0.5f; }
			else
			{
				total_mass = *_e->mass_pointer + *nearest_entity_left_side->mass_pointer;
				total_impulse = (*_e->mass_pointer * *_e->speed_x) + (*nearest_entity_left_side->mass_pointer * *nearest_entity_left_side->speed_x);

				*_e->speed_x = total_impulse / total_mass;
				*nearest_entity_left_side->speed_x = total_impulse / total_mass;
			}
		}



		if (_e->action_on_hit != NULL) { _e->action_on_hit(_e, nearest_entity_left_side, Entity::Side::HIT_SIDE_LEFT); }
		if (_e->action_on_hited != NULL) { _e->action_on_hited(nearest_entity_left_side, _e, Entity::Side::HIT_SIDE_LEFT); }
		//*e->position_x -= 1.0f;
	}

	if (nearest_entity_right_side != NULL)
	{
		if ((*_e->speed_x) < (*nearest_entity_right_side->speed_x))
		{
			*_e->speed_y *= pow(0.1, _d);

			if (*nearest_entity_right_side->inmovable) { *_e->speed_x *= 0.5f; }
			else
			{
				total_mass = *_e->mass_pointer + *nearest_entity_right_side->mass_pointer;
				total_impulse = (*_e->mass_pointer * *_e->speed_x) + (*nearest_entity_right_side->mass_pointer * *nearest_entity_right_side->speed_x);

				*_e->speed_x = total_impulse / total_mass;
				*nearest_entity_right_side->speed_x = total_impulse / total_mass;
			}
			//*e->position_x -= 1.0f;
		}

		*_e->position_x = *nearest_entity_right_side->position_x + *nearest_entity_right_side->collision_right + *_e->collision_left;

		if (_e->action_on_hit != NULL) { _e->action_on_hit(_e, nearest_entity_right_side, Entity::Side::HIT_SIDE_RIGHT); }
		if (_e->action_on_hited != NULL) { _e->action_on_hited(nearest_entity_right_side, _e, Entity::Side::HIT_SIDE_RIGHT); }
	}

	if (nearest_entity_up_side != NULL)
	{
		if ((*_e->speed_y) < (*nearest_entity_up_side->speed_y))
		{
			*_e->speed_x *= pow(0.1, _d);

			if (*nearest_entity_up_side->inmovable) { *_e->speed_y *= 0.5f; }
			else
			{
				total_mass = *_e->mass_pointer + *nearest_entity_up_side->mass_pointer;
				total_impulse = (*_e->mass_pointer * *_e->speed_y) + (*nearest_entity_up_side->mass_pointer * *nearest_entity_up_side->speed_y);

				*_e->speed_y = total_impulse / total_mass;
				*nearest_entity_up_side->speed_y = total_impulse / total_mass;
			}
			//*e->position_x -= 1.0f;
		}

		*_e->position_y = *nearest_entity_up_side->position_y + *nearest_entity_up_side->collision_up + *_e->collision_down;

		if (_e->action_on_hit != NULL) { _e->action_on_hit(_e, nearest_entity_up_side, Entity::Side::HIT_SIDE_UP); }
		if (_e->action_on_hited != NULL) { _e->action_on_hited(nearest_entity_up_side, _e, Entity::Side::HIT_SIDE_UP); }
	}

	if (nearest_entity_down_side != NULL)
	{
		if ((*_e->speed_y) > (*nearest_entity_down_side->speed_y))
		{
			*_e->speed_x *= pow(0.1, _d);

			if (*nearest_entity_down_side->inmovable) { *_e->speed_y *= 0.5f; }
			else
			{
				total_mass = *_e->mass_pointer + *nearest_entity_down_side->mass_pointer;
				total_impulse = (*_e->mass_pointer * *_e->speed_y) + (*nearest_entity_down_side->mass_pointer * *nearest_entity_down_side->speed_y);

				*_e->speed_y = total_impulse / total_mass;
				*nearest_entity_down_side->speed_y = total_impulse / total_mass;
				//*e->position_x -= 1.0f;
			}
		}

		*_e->position_y = *nearest_entity_down_side->position_y - *nearest_entity_down_side->collision_down - *_e->collision_up;

		if (_e->action_on_hit != NULL) { _e->action_on_hit(_e, nearest_entity_down_side, Entity::Side::HIT_SIDE_DOWN); }
		if (_e->action_on_hited != NULL) { _e->action_on_hited(nearest_entity_down_side, _e, Entity::Side::HIT_SIDE_DOWN); }
	}
}

bool Entity::can_see(Entity* _e, Entity* _target, float _d)
{
	//*_e->already_updated = true;


	////////////////////////////////////////////////////////////////////////////////////////////////////////

	*_e->target_vector_x =  *_target->position_x - *_e->position_x;
	*_e->target_vector_y =  *_target->position_y - *_e->position_y;

	int start_cluster_x = int(*_e->position_x / ECluster::CLUSTER_SIZE);
	int start_cluster_y = int(*_e->position_y / ECluster::CLUSTER_SIZE);

	if (*_e->target_vector_x > 0) { start_cluster_x -= 3; }
	else { start_cluster_x += 3; }
	if (*_e->target_vector_y > 0) { start_cluster_y -= 3; }
	else { start_cluster_y += 3; }
	//if (*e->real_speed_y > 0) { start_cluster_y -= 3; } else { start_cluster_y += 3; }

	int end_cluster_x = int((*_target->position_x) / ECluster::CLUSTER_SIZE);
	int end_cluster_y = int((*_target->position_y) / ECluster::CLUSTER_SIZE);
	if (*_e->target_vector_x > 0) { end_cluster_x += 3; }
	else { end_cluster_x -= 3; }
	if (*_e->target_vector_y > 0) { end_cluster_y += 3; }
	else { end_cluster_y -= 3; }


	int cluster_length_x = end_cluster_x - start_cluster_x;
	int cluster_length_y = end_cluster_y - start_cluster_y;

	int direction_x = 1;
	int direction_y = 1;

	if (cluster_length_x < 0) { direction_x = -1; }
	if (cluster_length_y < 0) { direction_y = -1; }

	int progress_x = 0;
	int progress_y = 0;


	for (int cx = start_cluster_x; cx != end_cluster_x + direction_x; cx += direction_x)
	{
		float projection_x = start_cluster_x;
		float projection_y = start_cluster_y;

		if (cluster_length_x != 0)
		{
			projection_x = cx;
			projection_y = start_cluster_y + cluster_length_y * progress_x / abs(cluster_length_x);
		}


		progress_y = 0;

		for (int cy = start_cluster_y; cy != end_cluster_y + direction_y; cy += direction_y)
			if
				(
				(cx >= 0) && (cy >= 0) && (cx < ECluster::CLUSTER_DIM) && (cy < ECluster::CLUSTER_DIM)
					&
					(
					(abs(projection_y - cy) <= 3)
						||
						(
						(progress_x <= 7) & (progress_y <= 7)
							)
						||
						(
						(progress_x >= abs(cluster_length_x) - 7) & (progress_y >= abs(cluster_length_y) - 7)
							)
						)
					)
			{
				if ((*_e->controlled_by_player) & ((EWindow::window_editor->is_active) || (false)) & (false))
				{
					if (abs(projection_y - cy) <= 3)
					{
						EGraphicCore::batch->setcolor_alpha(EColor::COLOR_PINK, 0.5f);
					}
					else
					{
						EGraphicCore::batch->setcolor_alpha(EColor::COLOR_PINK, 0.2f);
					}
					EGraphicCore::batch->draw_gabarite(cx * ECluster::CLUSTER_SIZE, cy * ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, EGraphicCore::gabarite_white_pixel);


					//EGraphicCore::batch->setcolor_alpha(EColor::COLOR_GREEN, 0.2f);
					//EGraphicCore::batch->draw_gabarite(projection_x * ECluster::CLUSTER_SIZE, projection_y * ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, EGraphicCore::gabarite_white_pixel);
				}




					//left_side
					if (*_e->target_vector_x > 0)
					{
						for (Entity* e2 : ECluster::clusters[cx][cy]->entity_list)
							if ((_e != e2) & (!*e2->is_bullet) & (!*e2->is_ghost))
							{
								if (ECluster::collision_left_zero_volume(_e, e2)) {if (e2 != _target) { return false; }}
							}
					}

					//right_side
					if (*_e->target_vector_x < 0)
					{

						for (Entity* e2 : ECluster::clusters[cx][cy]->entity_list)
							if ((_e != e2) & (!*e2->is_bullet) & (!*e2->is_ghost))
							{
								if (ECluster::collision_right_zero_volume(_e, e2)) { if (e2 != _target) { return false; } }
							}
					}
				


					//up_side
					if (*_e->target_vector_y < 0)
					{
						for (Entity* e2 : ECluster::clusters[cx][cy]->entity_list)
							if ((_e != e2) & (!*e2->is_bullet) & (!*e2->is_ghost))
							{
								if (ECluster::collision_up_zero_volume(_e, e2)) { if (e2 != _target) { return false; } }
							}
					}

					//down_side
					if (*_e->target_vector_y > 0)
					{
						for (Entity* e2 : ECluster::clusters[cx][cy]->entity_list)
							if ((_e != e2) & (!*e2->is_bullet) & (!*e2->is_ghost))
							{
								if (ECluster::collision_down_zero_volume(_e, e2)) { if (e2 != _target) { return false; } }
							}
					}
				

				progress_y++;
			}
			else
			{
				progress_y++;
			}

		progress_x++;
	}


	return true;
}

Entity::Entity()
{

	hp_pointer											= &eattr_current.at(EntityCurrentAttribute::CURRENT_LIFE);
	max_hp_pointer										= &eattr_TOTAL.at(EAttr::EA_LIFE);

	shield_pointer										= &eattr_current.at(EntityCurrentAttribute::CURRENT_SHIELD);
	max_shield_pointer									= &eattr_TOTAL.at(EAttr::EA_SHIELD);

	shield_overload_capacity_pointer					= &eattr_current.at(EntityCurrentAttribute::CURRENT_SHIELD_OVERLOAD_CAPACITY);
	max_shield_overload_capacity_pointer				= &eattr_TOTAL.at(EAttr::ENTITY_ATTRIBUTE_SHIELD_OVERLOAD_CAPACITY);

	shield_overload_duration_pointer					= &eattr_current.at(EntityCurrentAttribute::CURRENT_SHIELD_OVERLOAD_DURATION);
	max_shield_overload_duration_pointer				= &eattr_TOTAL.at(EAttr::ENTITY_ATTRIBUTE_SHIELD_OVERLOAD_DURATION);

	mass_pointer										= &eattr_TOTAL.at(EAttr::ENTITY_ATTRIBUTE_MASS);
	speed_pointer										= &eattr_TOTAL.at(EAttr::ENTITY_ATTRIBUTE_SPEED);
	shadow_tall_pointer									= &eattr_TOTAL.at(EAttr::ENTITY_ATTRIBUTE_SHADOW_TALL);
	drag_pointer										= &eattr_TOTAL.at(EAttr::ENTITY_ATTRIBUTE_DRAG);

	pointer_to_bool_list.at(EntityBoolAttributes::ENTITY_BOOL_ATTRIBUTE_INMOVABLE) =	inmovable;
	pointer_to_bool_list.at(EntityBoolAttributes::ENTITY_BOOL_CONTROLLED_BY_AI) =		controlled_by_ai;
	pointer_to_bool_list.at(EntityBoolAttributes::ENTITY_BOOL_CONTROLLED_BY_PLAYER) =	controlled_by_player;
	pointer_to_bool_list.at(EntityBoolAttributes::ENTITY_BOOL_HAVE_LIGHT_SOURCE) =		have_light_source;
	pointer_to_bool_list.at(EntityBoolAttributes::ENTITY_BOOL_GHOST) =					is_ghost;
	pointer_to_bool_list.at(EntityBoolAttributes::ENTITY_BOOL_NO_PATH_BLOCK) =			no_path_block;
	pointer_to_bool_list.at(EntityBoolAttributes::ENTITY_BOOL_NO_LIGHT_BLOCK) =			no_light_block;

	light_source_red									= &eattr_TOTAL.at(EAttr::ENTITY_ATTRIBUTE_LIGHT_SOURCE_RED);
	light_source_green									= &eattr_TOTAL.at(EAttr::ENTITY_ATTRIBUTE_LIGHT_SOURCE_GREEN);
	light_source_blue									= &eattr_TOTAL.at(EAttr::ENTITY_ATTRIBUTE_LIGHT_SOURCE_BLUE);

	//inmovable_pointer									= &eattr_bool.at(EntityBoolAttributes::ENTITY_BOOL_ATTRIBUTE_INMOVABLE);
	/*
	*max_hp_pointer = 4500.0f;
	EString::out_debug("life before: " + std::to_string(*max_hp_pointer));

	*max_hp_pointer = 9500.0f;
	EString::out_debug("life after: " + std::to_string(*max_hp_pointer));
	*/

	//EString::out_debug("size of vector: " + std::to_string(attribute_list.size()));
	//int n = 3;
	//attribute_list(n, 0.0f);
	//already_updated = false;
	/*
	ESprite* sp = new ESprite();

	sprite_list.push_back(sp);
	sp->gabarite.push_back(ETextureAtlas::put_texture_to_atlas("data/textures/sphere.png", EWindow::default_texture_atlas));

	sp->offset_x.push_back(-25.0f);
	sp->offset_y.push_back(0.0f);*/


}

Entity::~Entity()
{
}

void Entity::draw_sprite(Entity* _e, Batcher* _b, float _d, bool _is_shadow_mode, bool _transparent_is_height)
{
	
	EGabarite* link;
	int sprite_id = 0;


	


	for (ESprite* spr : _e->sprite_list)
	if (*spr->is_shadow == _is_shadow_mode)
	{
		int end_frame = 1;
		if (*spr->wall_mode) { end_frame = 3; }
		int frame_id = 0;

		float rotator_x = 0.0f;
		float rotator_y = 0.0f;

		float offset_x_begin = 0.0f;
		float offset_y_begin = 0.0f;

		if (*spr->rotate_by_move)
		{
			if (*_e->speed_x * *_e->speed_x > *_e->speed_y* *_e->speed_y)
			{
				if (*_e->speed_x > 0) { frame_id = 1;}
				else { frame_id = 3;}
			}
			else
			{
				if (*_e->speed_y > 0) { frame_id = 0;}
				else { frame_id = 2;}
			}

			if ((EWindow::window_editor->is_active) & (sprite_id == EWindow::window_editor->selected_sprite_id)) {frame_id = EWindow::window_editor->selected_frame_id;}
		}


		if (*spr->rotate_by_target_gun)
		{
			frame_id = *_e->target_angle_id;

			if (*_e->speed_x * *_e->speed_x > * _e->speed_y** _e->speed_y)
			{if (*_e->speed_x > 0) { offset_y_begin = 0.0f; } else { offset_y_begin = -0.0f; }}
			else
			{if (*_e->speed_y > 0) { offset_x_begin = -0.0f; } else { offset_x_begin = 0.0f; }}

			if ((EWindow::window_editor->is_active) & (sprite_id == EWindow::window_editor->selected_sprite_id)) { frame_id = EWindow::window_editor->selected_frame_id; }
		}

		//link = spr->gabarite.at(sprite_id);

		//spr->sprite_struct_list.at(0)->copies = 1;

		if (!spr->sprite_struct_list.empty())//if non empty sprite list
		if (spr->sprite_struct_list.at(frame_id)->gabarite != NULL)
		for (int f=0; f<end_frame; f++)
		for (int i=0; i < *spr->sprite_struct_list.at(frame_id)->copies; i++)
		{

			if (*spr->wall_mode)
			{
				if (f == 0)//wall
				{
					frame_id = 1;
					offset_x_begin = *spr->sprite_struct_list.at(0)->gabarite->size_x * *spr->sprite_struct_list.at(0)->copies + *spr->sprite_struct_list.at(0)->offset_x;
					offset_y_begin = *spr->sprite_struct_list.at(0)->offset_y;
				}
				else
				if (f == 1)//left corner
				{
					frame_id = 0;
					offset_x_begin = 0.0f;
					offset_y_begin = 0.0f;
				}
				else//right corner
				{
					frame_id = 2;

					offset_x_begin
					=
					*spr->sprite_struct_list.at(0)->gabarite->size_x * *spr->sprite_struct_list.at(0)->copies + *spr->sprite_struct_list.at(0)->offset_x
					+
					*spr->sprite_struct_list.at(1)->gabarite ->size_x * *spr->sprite_struct_list.at(1)->copies + *spr->sprite_struct_list.at(1)->offset_x;

					offset_y_begin = *spr->sprite_struct_list.at(0)->offset_y + *spr->sprite_struct_list.at(2)->offset_y;
				}
				//frame_id = f;
			}

			if
				(
					(!_is_shadow_mode)
					&
					(EWindow::window_editor->is_active)
					&&
					(EWindow::window_editor->sprite_flash_cooldown < 0.5f)
					&
					(
					(EWindow::window_editor->selected_entity == _e)
					||
					(find(EWindow::window_editor->selected_entity_list.begin(), EWindow::window_editor->selected_entity_list.end(), _e) != EWindow::window_editor->selected_entity_list.end())
				)
				&
				(
					(
						(EWindow::window_editor->selected_sprite_id == sprite_id)
						&
						(EWindow::window_editor->selected_frame_id == frame_id)
						&
						(EWindow::window_editor->editor_mode == EWindowEditor::EditMode::EditSprites)
					)
					||
					(EWindow::window_editor->editor_mode == EWindowEditor::EditMode::SelectEntities)
				)
			)
			{
				_b->setcolor_alpha(EColor::COLOR_GRAY,0.8f);
			}
			else
			{
				if (_is_shadow_mode)
				{
					if (_transparent_is_height)
					{_b->setcolor_alpha(EColor::COLOR_LAZURE_SHADOW, (*spr->sprite_struct_list.at(frame_id)->shadow_tall + *spr->sprite_struct_list.at(frame_id)->offset_z) / 512.0f);}
					else
					{_b->setcolor(EColor::COLOR_LAZURE_SHADOW);}

				}
				else
				{_b->setcolor(EColor::COLOR_SKY_AMBIENT);}
			}


			if (!_is_shadow_mode)
			{
				_b->draw_gabarite_shadowmap_fragment
				(
					*_e->position_x + *spr->sprite_struct_list.at(frame_id)->offset_x + i * *spr->sprite_struct_list.at(frame_id)->gabarite->size_x + offset_x_begin,
					*_e->position_y + *spr->sprite_struct_list.at(frame_id)->offset_y + offset_y_begin + *spr->sprite_struct_list.at(frame_id)->offset_z,

					0.0f,
					*spr->sprite_struct_list.at(frame_id)->gabarite->size_y,

					spr->sprite_struct_list.at(frame_id)->gabarite,
					spr->sprite_struct_list.at(frame_id)->supermap,
					*spr->sprite_struct_list.at(frame_id)->offset_z,
					*spr->sprite_struct_list.at(frame_id)->fragment_x,
					*spr->sprite_struct_list.at(frame_id)->fragment_y
				);
			}
			else
			{
				_b->draw_gabarite_skew
				(
					*_e->position_x + *spr->sprite_struct_list.at(frame_id)->offset_x + i * *spr->sprite_struct_list.at(frame_id)->gabarite->size_x + offset_x_begin,
					*_e->position_y + *spr->sprite_struct_list.at(frame_id)->offset_y + offset_y_begin + *spr->sprite_struct_list.at(frame_id)->offset_y,

					*spr->sprite_struct_list.at(frame_id)->shadow_size_x,
					*spr->sprite_struct_list.at(frame_id)->shadow_size_y,
					*spr->sprite_struct_list.at(frame_id)->shadow_tall,

					spr->sprite_struct_list.at(frame_id)->gabarite,
					*spr->sprite_struct_list.at(frame_id)->bottom_tall
				);
			}

			/*
			if (i + 1>= spr->copies.at(frame_id))
			{
				offset_x_begin += spr->gabarite.at(frame_id)->size_x * spr->copies.at(frame_id) + spr->offset_x.at(frame_id);
				offset_y_begin += spr->offset_y.at(frame_id);
			}*/

			if ((EWindow::window_editor->editor_mode == EWindowEditor::EditMode::EditSprites)&(true))
			{
				EGraphicCore::batch->setcolor(EColor::COLOR_RED);
				EGraphicCore::batch->draw_gabarite
				(
					*_e->position_x + *spr->sprite_struct_list.at(frame_id)->offset_x - 1.0f,
					*_e->position_y + *spr->sprite_struct_list.at(frame_id)->offset_y - 1.0f,

					3.0f,
					3.0f,

					EGraphicCore::gabarite_white_pixel
				);



			}
		}

		sprite_id++;
	}
	else
	{
		sprite_id++;
	}


	if ((EWindow::window_editor->editor_mode == EWindowEditor::EditMode::EditSprites) & (false))
	{
		_b->setcolor(EColor::COLOR_GREEN);
		_b->draw_gabarite
		(
			*_e->position_x - 1.0f,
			*_e->position_y - 1.0f,

			3.0f,
			3.0f,

			EGraphicCore::gabarite_white_pixel
		);
	}
}

void Entity::update_path_block(Entity* _e)
{
	
		int path_pos_x = int(*_e->position_x / EPath::PATH_SIZE);
		int path_pos_y = int(*_e->position_y / EPath::PATH_SIZE);

		int cluster_pos_x = int(*_e->position_x / ECluster::CLUSTER_SIZE);
		int cluster_pos_y = int(*_e->position_y / ECluster::CLUSTER_SIZE);

		//clear block
		for (int j = path_pos_x - 20; j <= path_pos_x + 20; j++)
		for (int i = path_pos_y - 20; i <= path_pos_y + 20; i++)
		if ((j >= 0) & (j < EPath::PATH_DIM) & (i >= 0) & (i < EPath::PATH_DIM))
		{
			EPath::block[j][i] = false;
		}

		//set block
	
	
		spread_path_block(_e);
}

void Entity::spread_path_block(Entity* _e)
{
	
		float safe_border = 5.0f;

		int cluster_pos_x = int(*_e->position_x / ECluster::CLUSTER_SIZE);
		int cluster_pos_y = int(*_e->position_y / ECluster::CLUSTER_SIZE);

		for (int cj = cluster_pos_x - 8; cj <= cluster_pos_x + 8; cj++)
			for (int ci = cluster_pos_y - 8; ci <= cluster_pos_y + 8; ci++)
				if ((cj >= 0) & (cj < ECluster::CLUSTER_DIM) & (ci >= 0) & (ci < ECluster::CLUSTER_DIM))
					for (Entity* e : ECluster::clusters[cj][ci]->entity_list)
						if ((*e->inmovable) & (!*e->no_path_block) & (!*e->is_ghost))
						{
							int block_start_x = (EMath::clamp_value_int((int)((*e->position_x - *e->path_block_gabarite_left + 15.0f * 0.0f) / EPath::PATH_SIZE), 0, EPath::PATH_DIM));
							int block_end_x = (EMath::clamp_value_int((int)((*e->position_x + *e->path_block_gabarite_right - 15.0f * 0.0f) / EPath::PATH_SIZE), 0, EPath::PATH_DIM));

							int block_start_y = (EMath::clamp_value_int((int)((*e->position_y - *e->path_block_gabarite_down + 15.0f * 0.0f) / EPath::PATH_SIZE), 0, EPath::PATH_DIM));
							int block_end_y = (EMath::clamp_value_int((int)((*e->position_y + *e->path_block_gabarite_up - 15.0f * 0.0f) / EPath::PATH_SIZE), 0, EPath::PATH_DIM));

							for (int j = block_start_x; j <= block_end_x; j++)
								for (int i = block_start_y; i <= block_end_y; i++)
								{
									EPath::block[j][i] = true;
								}
						}

}
void Entity::update_entity_attributes(Entity* _e)
{
	_e->eattr_BASE.at(EAttr::EA_LIFE) = 1000.0f;

	for (int i = 0; i < EAttr::_LAST_ELEMENT_OF_EA; i++)
	{
		_e->eattr_MORE.at(i) = 1.0f;
		_e->eattr_TOTAL.at(i) = _e->eattr_BASE.at(i) * (1.0f + _e->eattr_INCREASE.at(i)) * (_e->eattr_MORE.at(i));
	}

	/*
	_e->eattr_BASE.at(EAttr::EA_LIFE) = 1000.0f;
	_e->eattr_MORE.at(EAttr::EA_LIFE) = 1.0f;

	_e->eattr_TOTAL.at(EAttr::EA_LIFE)
	=
	_e->eattr_BASE.at(EAttr::EA_LIFE) * (1.0f + _e->eattr_INCREASE.at(EAttr::EA_LIFE)) * (_e->eattr_MORE.at(EAttr::EA_LIFE));
	*/


}


void Entity::update_building_autogenerator_massive(Entity* _selected)
{
	EWindowEditor* ed = EWindow::window_editor;
	
	dolboyob = 0;
	if (_selected != NULL)
	{
		//ed->link_to_texture_variant_array->button_list.clear();
		//for (subsprite* b:_selected->autobuilding_floor_list.at(ed->selected_building_autogenerator_floor)->wall_list.at(ed->selected_building_autogenerator_wall)->texture_variant_list)
		
		//reactivate floor button
		

		for (EButton* b: EWindow::window_editor->link_to_texture_variant_array->button_list)
		{
			if
			(
				(_selected->autobuilding_floor_list.size() > 0)
				&&
				(_selected->autobuilding_floor_list.at(ed->autobuilding_selected_floor)->wall_list.size() > 0)
				&&
				(_selected->autobuilding_floor_list.at(ed->autobuilding_selected_floor)->wall_list.at(ed->autobuilding_selected_wall)->texture_variant_list.size() > 0)
				&&
				(dolboyob < _selected->autobuilding_floor_list.at(ed->autobuilding_selected_floor)->wall_list.at(ed->autobuilding_selected_wall)->texture_variant_list.size())
			)
			{

				EWindow::window_editor->link_to_texture_variant_array->button_list.at(dolboyob)->is_active = true;
				EWindow::window_editor->link_to_texture_variant_array->button_list.at(dolboyob)->gabarite
				=
				_selected->autobuilding_floor_list.at(ed->autobuilding_selected_floor)->
				wall_list.at(ed->autobuilding_selected_wall)->
				texture_variant_list.at(dolboyob)->
				texture;
			}
			else
			{
				EWindow::window_editor->link_to_texture_variant_array->button_list.at(dolboyob)->is_active = false;

				EWindow::window_editor->link_to_texture_variant_array->button_list.at(dolboyob)->gabarite = NULL;
			}

			dolboyob++;
		}

		//EWindow::window_editor->count_of_floors = id;

		dolboyob = 0;
		for (EButton* b : ed->link_to_floors_array->button_list)
		{
			if (dolboyob < _selected->autobuilding_floor_list.size())
			{
				b->is_active = true;
			}
			else
			{
				b->is_active = false;
			}

			dolboyob++;
		}

		std::cout << "floor list size" + std::to_string(_selected->autobuilding_floor_list.size()) << std::endl;
		EWindow::window_editor->count_of_floors = _selected->autobuilding_floor_list.size();
		//;
	}



	EWindow::window_editor->select_new_floor();
	EWindow::window_editor->select_new_variant();
}

void Entity::assembly_autobuilding_sprites(Entity* _e)
{
	/*for (building_autogen_massive* m : _e->autobuilding_floor_list)
	{
		for (wall_element* w : m->wall_list)
		{
			for (wall_texture_variant* v : w->texture_variant_list)
			{
				//if (v->texture != NULL)		{ delete (v->texture);}
				//if (v->supermap != NULL)	{ delete (v->supermap);}
				//delete (v);
			}

			w->texture_variant_list.clear();
		}
	}
	//_e->sprite_list*/

	for (ESprite* s : _e->sprite_list)
	{
		delete s;
		//s = NULL;
	}

	_e->sprite_list.clear();
	

	float ox = 0.0f;
	float oy = 0.0f;
	float oz = 0.0f;

	ESprite* spr = NULL;
	Entity::wall_element* selected_wall = NULL;
	Entity::wall_texture_variant* selected_variant = NULL;
	EGabarite* selected_texture = NULL;

	//Entity::WallElementIndex ewe;

	for (int z=0; z<EWindow::window_editor->count_of_floors; z++)
	//for (Entity::building_autogen_floor* floor : _e->autobuilding_floor_list)
	{
		Entity::building_autogen_floor* floor = _e->autobuilding_floor_list.at(z);

		int random_select = 0;



		if (floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->texture_variant_list.size() > 0)
		{
			//mid wall

			for (int yy = 0;	yy	< ceil(*floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->repeat_y); yy++)
			for (int i = 0;		i	< ceil(*floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->repeat_x); i++)
			{
				spr = new ESprite(); //m->wall_list.at(0)


				ox =
					*floor->offset_x
					+
					*floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->offset_x
					+
					*floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->texture_variant_list.at(random_select)->offset_x;
					
				if (floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->texture_variant_list.at(random_select)->texture != NULL)
				{ox += *floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->texture_variant_list.at(random_select)->texture->size_x * i;}


				if (floor->wall_list.at(Entity::WallElementIndex::WEI_LEFT_WALL)->texture_variant_list.size() > 0)
				{
					if (floor->wall_list.at(Entity::WallElementIndex::WEI_LEFT_WALL)->texture_variant_list.at(random_select)->texture != NULL)
					{
						ox += *floor->wall_list.at(Entity::WallElementIndex::WEI_LEFT_WALL)->texture_variant_list.at(random_select)->texture->size_x;
					}
				}

				///////

				oy =
					*floor->offset_y
					+
					*floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->offset_y
					+
					*floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->texture_variant_list.at(random_select)->offset_y;

				if (floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->texture_variant_list.at(random_select)->texture != NULL)
				{
					oy += *floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->texture_variant_list.at(random_select)->texture->size_y * yy;
				}

				oz=
				*floor->offset_z
				+
				*floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->offset_z
				+
				*floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->texture_variant_list.at(random_select)->offset_z;


				spr->sprite_struct_list.at(0)->gabarite = floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->texture_variant_list.at(random_select)->texture;

				*spr->sprite_struct_list.at(0)->offset_x = ox;
				*spr->sprite_struct_list.at(0)->offset_y = oy;
				*spr->sprite_struct_list.at(0)->offset_z = oz;

				*spr->sprite_struct_list.at(0)->fragment_x = min(*floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->repeat_x - i, 1.0f);
				*spr->sprite_struct_list.at(0)->fragment_y = min(*floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->repeat_y - yy, 1.0f);

				_e->sprite_list.push_back(spr);
			}
		}
	
		//left wall
		for (int yy = 0; yy < ceil(*floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->repeat_y); yy++)
		if (floor->wall_list.at(Entity::WallElementIndex::WEI_LEFT_WALL)->texture_variant_list.size() > 0)
		{
			spr = new ESprite();

			ox =
				*floor->offset_x
				+
				*floor->wall_list.at(Entity::WallElementIndex::WEI_LEFT_WALL)->offset_x
				+
				*floor->wall_list.at(Entity::WallElementIndex::WEI_LEFT_WALL)->texture_variant_list.at(random_select)->offset_x;

			oy =
				*floor->offset_y
				+
				*floor->wall_list.at(Entity::WallElementIndex::WEI_LEFT_WALL)->offset_y
				+
				*floor->wall_list.at(Entity::WallElementIndex::WEI_LEFT_WALL)->texture_variant_list.at(random_select)->offset_y;

			if (floor->wall_list.at(Entity::WallElementIndex::WEI_LEFT_WALL)->texture_variant_list.at(random_select)->texture != NULL)
			{
				oy += *floor->wall_list.at(Entity::WallElementIndex::WEI_LEFT_WALL)->texture_variant_list.at(random_select)->texture->size_y * yy;
			}


			oz =
				*floor->offset_z
				+
				*floor->wall_list.at(Entity::WallElementIndex::WEI_LEFT_WALL)->offset_z
				+
				*floor->wall_list.at(Entity::WallElementIndex::WEI_LEFT_WALL)->texture_variant_list.at(random_select)->offset_z;

			spr->sprite_struct_list.at(0)->gabarite = floor->wall_list.at(Entity::WallElementIndex::WEI_LEFT_WALL)->texture_variant_list.at(random_select)->texture;

			*spr->sprite_struct_list.at(0)->offset_x = ox;
			*spr->sprite_struct_list.at(0)->offset_y = oy;
			*spr->sprite_struct_list.at(0)->offset_z = oz;

			_e->sprite_list.push_back(spr);

			*spr->sprite_struct_list.at(0)->fragment_y = min(*floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->repeat_y - yy, 1.0f);
		}

			//right wall
			for (int yy = 0; yy < ceil(*floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->repeat_y); yy++)
			if (floor->wall_list.at(Entity::WallElementIndex::WEI_RIGHT_WALL)->texture_variant_list.size() > 0)
			{
				spr = new ESprite();

				selected_wall = floor->wall_list.at(Entity::WallElementIndex::WEI_RIGHT_WALL);
				selected_variant = selected_wall->texture_variant_list.at(random_select);
				selected_texture = selected_variant->texture;

				ox =
					*floor->offset_x
					+
					*selected_wall->offset_x + *selected_variant->offset_x;
				
				// + size of left wall
				if (floor->wall_list.at(Entity::WallElementIndex::WEI_LEFT_WALL)->texture_variant_list.size() > 0)
				{
					if (floor->wall_list.at(Entity::WallElementIndex::WEI_LEFT_WALL)->texture_variant_list.at(random_select)->texture != NULL)
					ox += *floor->wall_list.at(Entity::WallElementIndex::WEI_LEFT_WALL)->texture_variant_list.at(random_select)->texture->size_x * (*floor->wall_list.at(Entity::WallElementIndex::WEI_LEFT_WALL)->repeat_x);
				}

				// + size of mid wall
				if (floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->texture_variant_list.size() > 0)
				{
					if (floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->texture_variant_list.at(random_select)->texture != NULL)
					ox += *floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->texture_variant_list.at(random_select)->texture->size_x* (*floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->repeat_x);
				}


				oy = *floor->offset_y + *selected_wall->offset_y + *selected_variant->offset_y;

				if (floor->wall_list.at(Entity::WallElementIndex::WEI_RIGHT_WALL)->texture_variant_list.at(random_select)->texture != NULL)
				{
					oy += *floor->wall_list.at(Entity::WallElementIndex::WEI_RIGHT_WALL)->texture_variant_list.at(random_select)->texture->size_y * yy;
				}

				oz = *floor->offset_z + *selected_wall->offset_z + *selected_variant->offset_z;

				if (floor->wall_list.at(2)->texture_variant_list.size() > 0)
				{
					spr->sprite_struct_list.at(0)->gabarite = floor->wall_list.at(2)->texture_variant_list.at(random_select)->texture;
				}

				*spr->sprite_struct_list.at(0)->offset_x = ox;
				*spr->sprite_struct_list.at(0)->offset_y = oy;
				*spr->sprite_struct_list.at(0)->offset_z = oz;

				_e->sprite_list.push_back(spr);
				*spr->sprite_struct_list.at(0)->fragment_y = min(*floor->wall_list.at(Entity::WallElementIndex::WEI_MID_WALL)->repeat_y - yy, 1.0f);

			}

			spr = new ESprite();
			_e->sprite_list.push_back(spr);
			spr->sprite_struct_list.at(0)->gabarite = EGraphicCore::gabarite_white_pixel;
			*spr->is_shadow = true;
			*spr->sprite_struct_list.at(0)->shadow_size_x = ox;
			*spr->sprite_struct_list.at(0)->shadow_size_y = 100.0f;
			*spr->sprite_struct_list.at(0)->bottom_tall = 100.0f;
			*spr->sprite_struct_list.at(0)->shadow_tall = 100.0f;
			*spr->sprite_struct_list.at(0)->shadow_height = 100.0f;

			*spr->sprite_struct_list.at(0)->offset_x = ox;
			*spr->sprite_struct_list.at(0)->offset_y = oy;
			*spr->sprite_struct_list.at(0)->offset_z = oz;
		}

	
}

/*void Entity::draw_sprite_assembly(Entity* _e, Batcher* _b, float _d, bool _shadow_mode)
{
	int subsprite_id = 0;

	//draw regular batch
	if (!_shadow_mode)
	for (sprite_assembly* sa : _e->sprite_assembly_list)
	{
		_b->draw_gabarite_shadowmap
		(
			*_e->position_x + *sa->subsprite_list.at(subsprite_id)->offset_x,//position_x
			*_e->position_y + *sa->subsprite_list.at(subsprite_id)->offset_y,//position_y

			0.0f,
			sa->subsprite_list.at(subsprite_id)->texture->size_y,

			sa->subsprite_list.at(subsprite_id)->texture,
			sa->subsprite_list.at(subsprite_id)->supermap,
			*sa->subsprite_list.at(subsprite_id)->offset_z
		);
	}
}*/

bool ECluster::collision_left(Entity* _a, Entity* _b)
{
	float pseudo_line = *_b->position_x - *_b->collision_left - *_a->collision_right;

	if
	(
		(*_a->position_x <= pseudo_line)
		&&
		(*_a->position_x + *_a->target_vector_x >= pseudo_line)
		&&
		(*_a->position_y + *_a->target_vector_y / *_a->target_vector_x * (pseudo_line  - *_a->position_x) <= *_b->position_y + *_b->collision_up + *_a->collision_down)
		&&
		(*_a->position_y + *_a->target_vector_y / *_a->target_vector_x * (pseudo_line - *_a->position_x) >= *_b->position_y - *_b->collision_down - *_a->collision_up)
	)
	{ 
		
		EGraphicCore::batch->setcolor(EColor::COLOR_RED);
		EGraphicCore::batch->draw_gabarite(*_b->position_x - *_b->collision_left, *_b->position_y + *_b->collision_up + *_a->collision_down, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_b->position_x - *_b->collision_left, *_b->position_y - *_b->collision_down - *_a->collision_up, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_a->position_x, *_a->position_y, -*_a->collision_right, 1.0f, EGraphicCore::gabarite_white_pixel);

		EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
		EGraphicCore::batch->draw_gabarite(*_b->position_x + *_b->collision_left, *_a->position_y + *_a->target_vector_y / *_a->target_vector_x * (pseudo_line - *_a->position_x), 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		
		return true;
	}

	return false;
}

bool ECluster::collision_right(Entity* _a, Entity* _b)
{
	float pseudo_line = *_b->position_x + *_b->collision_right + *_a->collision_left;

	if
	(
		(*_a->position_x >= pseudo_line)
		&&
		(*_a->position_x + *_a->target_vector_x <= pseudo_line)
		&&
		(*_a->position_y - *_a->target_vector_y / *_a->target_vector_x * ( *_a->position_x - pseudo_line) <= *_b->position_y + *_b->collision_up + *_a->collision_down)
		&&
		(*_a->position_y - *_a->target_vector_y / *_a->target_vector_x * (*_a->position_x - pseudo_line) >= *_b->position_y - *_b->collision_down - *_a->collision_up)
		//500 + -500 / -500 * 500 - 0
		//500 + 1 * 500
	)
	{ 
		
		EGraphicCore::batch->setcolor(EColor::COLOR_RED);
		EGraphicCore::batch->draw_gabarite(*_b->position_x + *_b->collision_right, *_b->position_y + *_b->collision_up + *_a->collision_down, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_b->position_x + *_b->collision_right, *_b->position_y - *_b->collision_down - *_a->collision_up, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_a->position_x, *_a->position_y, -*_a->collision_left, 1.0f, EGraphicCore::gabarite_white_pixel);

		EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
		EGraphicCore::batch->draw_gabarite(*_b->position_x + *_b->collision_right, *_a->position_y - *_a->target_vector_y / *_a->target_vector_x * (*_a->position_x - pseudo_line), 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		
		return true;
	}

	return false;
}

bool ECluster::collision_up(Entity* _a, Entity* _b)
{
	float pseudo_line = *_b->position_y + *_b->collision_up + *_a->collision_down;

	if
	(
		(*_a->position_y >= pseudo_line)
		&&
		(*_a->position_y + *_a->target_vector_y <= pseudo_line)
		&&
		(*_a->position_x + *_a->target_vector_x / *_a->target_vector_y * ( pseudo_line - *_a->position_y ) <= *_b->position_x + *_b->collision_right + *_a->collision_left)
		&&
		(*_a->position_x + *_a->target_vector_x / *_a->target_vector_y * ( pseudo_line  - *_a->position_y ) >= *_b->position_x - *_b->collision_left - *_a->collision_right)
	)
	{ 
		
		EGraphicCore::batch->setcolor(EColor::COLOR_RED);
		EGraphicCore::batch->draw_gabarite(*_b->position_x + *_b->collision_right + *_a->collision_left, *_b->position_y + *_b->collision_up, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_b->position_x - *_b->collision_left - *_a->collision_right, *_b->position_y + *_b->collision_up, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_a->position_x, *_a->position_y, 1.0f, -*_a->collision_down, EGraphicCore::gabarite_white_pixel);

		EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
		EGraphicCore::batch->draw_gabarite(*_a->position_x + *_a->target_vector_x / *_a->target_vector_y * (pseudo_line - *_a->position_y), *_b->position_y + *_b->collision_up, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		

		return true;
	}

	return false;
}

bool ECluster::collision_down(Entity* _a, Entity* _b)
{
	float pseudo_line = *_b->position_y - *_b->collision_down - *_a->collision_up;

	if
	(
		(*_a->position_y <= pseudo_line)
		&&
		(*_a->position_y + *_a->target_vector_y >= pseudo_line)
		&&
		(*_a->position_x - *_a->target_vector_x / *_a->target_vector_y * ( *_a->position_y - pseudo_line) <= *_b->position_x + *_b->collision_right + *_a->collision_left)
		&&
		(*_a->position_x - *_a->target_vector_x / *_a->target_vector_y * ( *_a->position_y - pseudo_line) >= *_b->position_x - *_b->collision_left - *_a->collision_right)
	)
	{ 
		
		EGraphicCore::batch->setcolor(EColor::COLOR_RED);
		EGraphicCore::batch->draw_gabarite(*_b->position_x + *_b->collision_right + *_a->collision_left, *_b->position_y - *_b->collision_down, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_b->position_x - *_b->collision_left - *_a->collision_right, *_b->position_y - *_b->collision_down, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_a->position_x, *_a->position_y, 1.0f, *_a->collision_up, EGraphicCore::gabarite_white_pixel);

		EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
		EGraphicCore::batch->draw_gabarite(*_a->position_x - *_a->target_vector_x / *_a->target_vector_y * (*_a->position_y - pseudo_line), *_b->position_y - *_b->collision_down, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		
		return true;
	}


	return false;
}




bool ECluster::collision_left_zero_volume(Entity* _a, Entity* _b)
{
	float pseudo_line = *_b->position_x - *_b->collision_left;

	if
		(
		(*_a->position_x <= pseudo_line)
			&&
			(*_a->position_x + *_a->target_vector_x >= pseudo_line)
			&&
			(*_a->position_y + *_a->target_vector_y / *_a->target_vector_x * (pseudo_line - *_a->position_x) <= *_b->position_y + *_b->collision_up)
			&&
			(*_a->position_y + *_a->target_vector_y / *_a->target_vector_x * (pseudo_line - *_a->position_x) >= *_b->position_y - *_b->collision_down)
			)
	{

		EGraphicCore::batch->setcolor(EColor::COLOR_RED);
		EGraphicCore::batch->draw_gabarite(*_b->position_x - *_b->collision_left, *_b->position_y + *_b->collision_up, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_b->position_x - *_b->collision_left, *_b->position_y - *_b->collision_down, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_a->position_x, *_a->position_y, 0.0f, 1.0f, EGraphicCore::gabarite_white_pixel);

		EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
		EGraphicCore::batch->draw_gabarite(*_b->position_x + *_b->collision_left, *_a->position_y + *_a->target_vector_y / *_a->target_vector_x * (pseudo_line - *_a->position_x), 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);

		return true;
	}

	return false;

	return true;
}

bool ECluster::collision_right_zero_volume(Entity* _a, Entity* _b)
{
	float pseudo_line = *_b->position_x + *_b->collision_right;

	if
		(
		(*_a->position_x >= pseudo_line)
			&&
			(*_a->position_x + *_a->target_vector_x <= pseudo_line)
			&&
			(*_a->position_y - *_a->target_vector_y / *_a->target_vector_x * (*_a->position_x - pseudo_line) <= *_b->position_y + *_b->collision_up)
			&&
			(*_a->position_y - *_a->target_vector_y / *_a->target_vector_x * (*_a->position_x - pseudo_line) >= *_b->position_y - *_b->collision_down)
			//500 + -500 / -500 * 500 - 0
			//500 + 1 * 500
			)
	{

		EGraphicCore::batch->setcolor(EColor::COLOR_RED);
		EGraphicCore::batch->draw_gabarite(*_b->position_x + *_b->collision_right, *_b->position_y + *_b->collision_up, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_b->position_x + *_b->collision_right, *_b->position_y - *_b->collision_down, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_a->position_x, *_a->position_y, 0.0f, 1.0f, EGraphicCore::gabarite_white_pixel);

		EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
		EGraphicCore::batch->draw_gabarite(*_b->position_x + *_b->collision_right, *_a->position_y - *_a->target_vector_y / *_a->target_vector_x * (*_a->position_x - pseudo_line), 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);

		return true;
	}

	return false;
}

bool ECluster::collision_down_zero_volume(Entity* _a, Entity* _b)
{
	float pseudo_line = *_b->position_y;

	if
		(
		(*_a->position_y <= pseudo_line)
			&&
			(*_a->position_y + *_a->target_vector_y >= pseudo_line)
			&&
			(*_a->position_x - *_a->target_vector_x / *_a->target_vector_y * (*_a->position_y - pseudo_line) <= *_b->position_x + *_b->collision_right)
			&&
			(*_a->position_x - *_a->target_vector_x / *_a->target_vector_y * (*_a->position_y - pseudo_line) >= *_b->position_x - *_b->collision_left)
			)
	{

		EGraphicCore::batch->setcolor(EColor::COLOR_RED);
		EGraphicCore::batch->draw_gabarite(*_b->position_x + *_b->collision_right, *_b->position_y - *_b->collision_down, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_b->position_x - *_b->collision_left, *_b->position_y - *_b->collision_down, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_a->position_x, *_a->position_y, 1.0f, 0.0f, EGraphicCore::gabarite_white_pixel);

		EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
		EGraphicCore::batch->draw_gabarite(*_a->position_x - *_a->target_vector_x / *_a->target_vector_y * (*_a->position_y - pseudo_line), *_b->position_y - *_b->collision_down, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);

		return true;
	}


	return false;
}

bool ECluster::collision_up_zero_volume(Entity* _a, Entity* _b)
{
	float pseudo_line = *_b->position_y + *_b->collision_up;

	if
		(
		(*_a->position_y >= pseudo_line)
			&&
			(*_a->position_y + *_a->target_vector_y <= pseudo_line)
			&&
			(*_a->position_x + *_a->target_vector_x / *_a->target_vector_y * (pseudo_line - *_a->position_y) <= *_b->position_x + *_b->collision_right)
			&&
			(*_a->position_x + *_a->target_vector_x / *_a->target_vector_y * (pseudo_line - *_a->position_y) >= *_b->position_x - *_b->collision_left)
			)
	{

		EGraphicCore::batch->setcolor(EColor::COLOR_RED);
		EGraphicCore::batch->draw_gabarite(*_b->position_x + *_b->collision_right, *_b->position_y + *_b->collision_up, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_b->position_x - *_b->collision_left, *_b->position_y + *_b->collision_up, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_a->position_x, *_a->position_y, 1.0f, 0.0f, EGraphicCore::gabarite_white_pixel);

		EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
		EGraphicCore::batch->draw_gabarite(*_a->position_x + *_a->target_vector_x / *_a->target_vector_y * (pseudo_line - *_a->position_y), *_b->position_y + *_b->collision_up, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);


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

int ECluster::cluster_on_mouse_x = 0;
int ECluster::cluster_on_mouse_y = 0;


void ECluster::put_entity(Entity* _e, float _x, float _y)
{
	*_e->position_x = _x;
	*_e->position_y = _y;

	int cluster_x =  EMath::clamp_value_int((int)(_x / CLUSTER_SIZE), 0, CLUSTER_DIM);
	int cluster_y =  EMath::clamp_value_int((int)(_y / CLUSTER_SIZE), 0, CLUSTER_DIM);

	clusters[cluster_x][cluster_y]->entity_list.push_back(_e);

	//int path_x = EMath::clamp_value_int((int)(_x / EPath::PATH_SIZE), 0, EPath::PATH_DIM);
	//int path_y = EMath::clamp_value_int((int)(_y / EPath::PATH_SIZE), 0, EPath::PATH_DIM);

	//EPath::block[path_x][path_y] += EPath::ENTITY_BLOCK_VALUE;
}

void ECluster::put_entity(Entity* _e)
{
	int cluster_x = EMath::clamp_value_int((int)(*_e->position_x / CLUSTER_SIZE), 0, CLUSTER_DIM);
	int cluster_y = EMath::clamp_value_int((int)(*_e->position_y / CLUSTER_SIZE), 0, CLUSTER_DIM);

	clusters[cluster_x][cluster_y]->entity_list.push_back(_e);
}

void ESprite::clear_default_data(ESprite* _sprite)
{
	_sprite->sprite_struct_list.clear();
}

void ESprite::set_default_data(ESprite* _sprite)
{
	EGabarite* g = EGraphicCore::gabarite_white_pixel;
	sprite_struct* ss = new sprite_struct;

	ss->gabarite =  ETextureAtlas::put_texture_to_atlas("data/textures/white_pixel.png", EWindow::default_texture_atlas);
	ss->supermap =  ETextureAtlas::put_texture_to_atlas("data/textures/white_pixel.png", EWindow::default_texture_atlas);

	_sprite->sprite_struct_list.push_back(ss);

}

ESprite::ESprite()
{
	sprite_struct_list.push_back(new sprite_struct);
	sprite_struct_list.at(0)->gabarite = ETextureAtlas::put_texture_to_atlas("data/textures/white_pixel.png", EWindow::default_texture_atlas);
	sprite_struct_list.at(0)->supermap = ETextureAtlas::put_texture_to_atlas("data/textures/white_pixel.png", EWindow::default_texture_atlas);
}

ESprite::~ESprite()
{
	for (sprite_struct* s : sprite_struct_list)
	{
		delete s;
	}

	delete rotate_by_move;
	delete rotate_by_target;
	delete wall_mode;
	delete is_shadow;
	delete rotate_by_target_gun;
}

EItem::EItem()
{
}

EItem::~EItem()
{
}

std::vector< EItem::affix_struct*> EItem::AFFIX_REGISTERER;

void EItem::update_item_attributes(EItem* _item)
{

	//reset increase/more/total values
	for (EItem::item_attributes_struct* ias : _item->item_attributes_list)
	{
		*ias->item_base_attr = 0.0f;

		*ias->item_increase_attr = 0.0f;
		*ias->item_more_attr = 1.0f;
		*ias->item_total_attr = 0.0f;
	}

	//set base values of attribute
	for (EItem::set_affix_base_valuse_struct* sbvl : _item->set_base_value_list)
	{

		float autopower = 1.0f;

		if (*sbvl->autopower_by_level) { autopower = *_item->item_level / 10.0f; }
		*_item->item_attributes_list.at(*sbvl->id)->item_base_attr = *sbvl->value * autopower;
	}


	//calculate increase/more/total values
	for (EItem::affix_struct* gal : _item->generated_affixes_list)
	{
		affix_tier_struct* selected_tier_affix = gal->affix_tier_list.at(*gal->selected_tier);
	
		for (affix_property* ap : selected_tier_affix->affix_property_list)
		{
			*_item->item_attributes_list.at(*ap->attribute_id)->item_base_attr += *ap->add_base;
			*_item->item_attributes_list.at(*ap->attribute_id)->item_increase_attr += *ap->increase;
			*_item->item_attributes_list.at(*ap->attribute_id)->item_more_attr *= 1.0f + *ap->increase;
		}
			//_item->item_attributes_list.at(ats->affix_property_list)

	}

	//calculate total attributes with all bonuses
	for (EItem::item_attributes_struct* ial : _item->item_attributes_list)
	{
		*ial->item_total_attr = *ial->item_base_attr * (*ial->item_increase_attr + 1.0f) * (*ial->item_more_attr);
	}


}

EItemAttribute::EItemAttribute()
{

}

EItemAttribute::~EItemAttribute()
{
}
