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

Entity::Entity()
{
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

void Entity::draw_sprite(Entity* _e, Batcher* _b, float _d, bool _is_shadow_mode)
{
	
	EGabarite* link;
	int sprite_id = 0;


	


	for (ESprite* spr : _e->sprite_list)
	if (*spr->is_shadow == _is_shadow_mode)
	{
		int end_frame = 1;
		if (*spr->wall_mode) { end_frame = 3; }
		int frame_id = 0;

		float offset_x_begin = 0.0f;
		float offset_y_begin = 0.0f;

		if (*spr->rotate_by_move)
		{
			if (*_e->speed_x * *_e->speed_x > *_e->speed_y* *_e->speed_y)
			{
				if (*_e->speed_x > 0) { frame_id = 1; }
				else { frame_id = 3; }
			}
			else
			{
				if (*_e->speed_y > 0) { frame_id = 0; }
				else { frame_id = 2; }
			}

			if (EWindow::window_editor->is_active)
			{
				frame_id = EWindow::window_editor->selected_frame_id;
			}
		}

		//link = spr->gabarite.at(sprite_id);
		if (!spr->gabarite.empty())
		if (spr->gabarite.at(frame_id) != NULL)
		for (int f=0; f<end_frame; f++)
		for (int i=0; i<spr->copies.at(frame_id); i++)
		{

			if (*spr->wall_mode)
			{
				if (f == 0)
				{
					frame_id = 1;
					offset_x_begin = spr->gabarite.at(0)->size_x * spr->copies.at(0) + spr->offset_x.at(0);
					offset_y_begin = spr->offset_y.at(0);
				}

				if (f == 1)
				{
					frame_id = 0;
					offset_x_begin = 0.0f;
					offset_y_begin = 0.0f;
				}

				if (f == 2)
				{
					frame_id = 2;

					offset_x_begin
					=
					spr->gabarite.at(0)->size_x * spr->copies.at(0) + spr->offset_x.at(0)
					+
					spr->gabarite.at(1)->size_x * spr->copies.at(1) + spr->offset_x.at(1);

					offset_y_begin = spr->offset_y.at(0) + spr->offset_y.at(2);
				}
				//frame_id = f;
			}
			if
				(
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
				EGraphicCore::batch->setcolor_alpha(EColor::COLOR_GRAY,0.8f);
			}
			else
			{
				EGraphicCore::batch->setcolor(EColor::COLOR_WHITE);
			}


			_b->draw_gabarite
			(
				*_e->position_x + spr->offset_x.at(frame_id) + i * spr->gabarite.at(frame_id)->size_x + offset_x_begin,
				*_e->position_y + spr->offset_y.at(frame_id) + offset_y_begin,

				spr->gabarite.at(frame_id)->size_x,
				spr->gabarite.at(frame_id)->size_y,

				spr->gabarite.at(frame_id)
			);

			/*
			if (i + 1>= spr->copies.at(frame_id))
			{
				offset_x_begin += spr->gabarite.at(frame_id)->size_x * spr->copies.at(frame_id) + spr->offset_x.at(frame_id);
				offset_y_begin += spr->offset_y.at(frame_id);
			}*/

			if (EWindow::window_editor->editor_mode == EWindowEditor::EditMode::EditSprites)
			{
				EGraphicCore::batch->setcolor(EColor::COLOR_RED);
				_b->draw_gabarite
				(
					*_e->position_x + spr->offset_x.at(frame_id) - 1.0f,
					*_e->position_y + spr->offset_y.at(frame_id) - 1.0f,

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

	if (EWindow::window_editor->editor_mode == EWindowEditor::EditMode::EditSprites)
	{
		EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
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

bool ECluster::collision_left(Entity* _a, Entity* _b)
{
	float pseudo_line = *_b->position_x - *_b->collision_left - *_a->collision_right;

	if
	(
		(*_a->position_x <= pseudo_line)
		&&
		(*_a->position_x + *_a->real_speed_x >= pseudo_line)
		&&
		(*_a->position_y + *_a->real_speed_y / *_a->real_speed_x * (pseudo_line  - *_a->position_x) <= *_b->position_y + *_b->collision_up + *_a->collision_down)
		&&
		(*_a->position_y + *_a->real_speed_y / *_a->real_speed_x * (pseudo_line - *_a->position_x) >= *_b->position_y - *_b->collision_down - *_a->collision_up)
	)
	{ 
		EGraphicCore::batch->setcolor(EColor::COLOR_RED);
		EGraphicCore::batch->draw_gabarite(*_b->position_x - *_b->collision_left, *_b->position_y + *_b->collision_up + *_a->collision_down, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_b->position_x - *_b->collision_left, *_b->position_y - *_b->collision_down - *_a->collision_up, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_a->position_x, *_a->position_y, -*_a->collision_right, 1.0f, EGraphicCore::gabarite_white_pixel);

		EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
		EGraphicCore::batch->draw_gabarite(*_b->position_x + *_b->collision_left, *_a->position_y + *_a->real_speed_y / *_a->real_speed_x * (pseudo_line - *_a->position_x), 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);

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
		(*_a->position_x + *_a->real_speed_x <= pseudo_line)
		&&
		(*_a->position_y + *_a->real_speed_y / *_a->real_speed_x * ( *_a->position_x - pseudo_line) <= *_b->position_y + *_b->collision_up + *_a->collision_down)
		&&
		(*_a->position_y + *_a->real_speed_y / *_a->real_speed_x * (*_a->position_x - pseudo_line) >= *_b->position_y - *_b->collision_down - *_a->collision_up)
	)
	{ 
		EGraphicCore::batch->setcolor(EColor::COLOR_RED);
		EGraphicCore::batch->draw_gabarite(*_b->position_x + *_b->collision_right, *_b->position_y + *_b->collision_up + *_a->collision_down, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_b->position_x + *_b->collision_right, *_b->position_y - *_b->collision_down - *_a->collision_up, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_a->position_x, *_a->position_y, -*_a->collision_left, 1.0f, EGraphicCore::gabarite_white_pixel);

		EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
		EGraphicCore::batch->draw_gabarite(*_b->position_x + *_b->collision_right, *_a->position_y + *_a->real_speed_y / *_a->real_speed_x * (*_a->position_x - pseudo_line), 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);

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
		(*_a->position_y + *_a->real_speed_y <= pseudo_line)
		&&
		(*_a->position_x + *_a->real_speed_x / *_a->real_speed_y * ( pseudo_line - *_a->position_y ) <= *_b->position_x + *_b->collision_right + *_a->collision_left)
		&&
		(*_a->position_x + *_a->real_speed_x / *_a->real_speed_y * ( pseudo_line  - *_a->position_y ) >= *_b->position_x - *_b->collision_left - *_a->collision_right)
	)
	{ 
		EGraphicCore::batch->setcolor(EColor::COLOR_RED);
		EGraphicCore::batch->draw_gabarite(*_b->position_x + *_b->collision_right + *_a->collision_left, *_b->position_y + *_b->collision_up, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_b->position_x - *_b->collision_left - *_a->collision_right, *_b->position_y + *_b->collision_up, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_a->position_x, *_a->position_y, 1.0f, -*_a->collision_down, EGraphicCore::gabarite_white_pixel);

		EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
		EGraphicCore::batch->draw_gabarite(*_a->position_x + *_a->real_speed_x / *_a->real_speed_y * (pseudo_line - *_a->position_y), *_b->position_y + *_b->collision_up, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);


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
		(*_a->position_y + *_a->real_speed_y >= pseudo_line)
		&&
		(*_a->position_x + *_a->real_speed_x / *_a->real_speed_y * ( *_a->position_y - pseudo_line) <= *_b->position_x + *_b->collision_right + *_a->collision_left)
		&&
		(*_a->position_x + *_a->real_speed_x / *_a->real_speed_y * ( *_a->position_y - pseudo_line) >= *_b->position_x - *_b->collision_left - *_a->collision_right)
	)
	{ 

		EGraphicCore::batch->setcolor(EColor::COLOR_RED);
		EGraphicCore::batch->draw_gabarite(*_b->position_x + *_b->collision_right + *_a->collision_left, *_b->position_y - *_b->collision_down, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_b->position_x - *_b->collision_left - *_a->collision_right, *_b->position_y - *_b->collision_down, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);
		EGraphicCore::batch->draw_gabarite(*_a->position_x, *_a->position_y, 1.0f, *_a->collision_up, EGraphicCore::gabarite_white_pixel);

		EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
		EGraphicCore::batch->draw_gabarite(*_a->position_x + *_a->real_speed_x / *_a->real_speed_y * (*_a->position_y - pseudo_line), *_b->position_y - *_b->collision_down, 5.0f, 5.0f, EGraphicCore::gabarite_white_pixel);

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
	_sprite->offset_x.clear();
	_sprite->offset_y.clear();
	_sprite->copies.clear();
	_sprite->gabarite.clear();
}

ESprite::ESprite()
{
	gabarite.push_back(EGraphicCore::gabarite_white_pixel);

	offset_x.push_back(0.0f);
	offset_y.push_back(0.0f);
	copies.push_back(1);
}

ESprite::~ESprite()
{
}
