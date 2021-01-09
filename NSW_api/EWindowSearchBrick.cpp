#include "EWindowSearchBrick.h"

# define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <fstream>
#include <iostream>
#include <experimental/filesystem>
#include "EBA.h"
namespace fs = std::experimental::filesystem;

EWindowSearchBrick::EWindowSearchBrick()
{

	//for (auto& p : fs::directory_iterator("data/textures"))std::cout << p << '\n';

	window_size_x = 700.0f;
	window_size_y = 800.0f;

	align_x = Enums::PositionMode::LEFT;

	EButton* but = new EButton(15.0f, -15.0f, 300.0f, 30.0f);
	but->master_window = this;
	but->input_auto_clear_text = true;
	but->have_input_mode = true;
	//but->any_input = true;
	but->is_input_mode_active = true;
	but->outclick_protection = true;

	but->action_on_input = &EBA::action_input_search_brick;

	but->position_mode_x = Enums::MID;
	but->position_mode_y = Enums::UP;

	link_to_input = but;
	button_list.push_back(but);

	float xx = 0;
	float yy = 0;
	list_of_textures.clear();

	//for (EGabarite* g: EGraphicCore::gabarite_list)
	for (auto& p : fs::directory_iterator("data/textures"))
	{
		

		but = new EButton(15.0f + xx, -50.0f + yy, 80.0f, 80.0f);
		but->master_window = this;

		but->position_mode_x = Enums::LEFT;
		but->position_mode_y = Enums::UP;
		but->have_icon = true;
		but->have_description = true;
		but->have_rama = true;

		//std::cout << "try load texture: " << p.path().filename().u8string() << std::endl;

		but->gabarite = ETextureAtlas::put_texture_to_atlas(p.path().u8string(), EWindow::default_texture_atlas);

		list_of_textures.push_back(but->gabarite);
		list_of_textures_names.push_back(p.path().filename().u8string().substr(0, p.path().filename().u8string().length() - 4));

		but->data_string = p.path().filename().u8string();//texture path
		but->description_text = p.path().filename().u8string();

		//but->button_action_press = new EButtonActionSetSpriteTexture();
		//but->action_on_left_click = &EBA::action_set_sprite_texture_for_autobuilding;

		brick_button.push_back(but);
		button_list.push_back(but);

		xx += 85.0f;
		if (xx + but->button_size_x > window_size_x)
		{
			xx = 0;
			yy -= 85.0f;
		}

		but->button_x = 15.0f + xx;
		but->button_y = -50.0f + yy;
	}



	always_fullscreen = false;
	have_bg = true;
	align_x = Enums::PositionMode::MID;
	align_x = Enums::PositionMode::MID;


}

EWindowSearchBrick::~EWindowSearchBrick()
{
}

void EWindowSearchBrick::update(float _d)
{
}

void EWindowSearchBrick::draw(float _d)
{
}

void EWindowSearchBrick::draw_interface(float _d)
{
	if (search_mode == SearchMode::SEARCH_ENTITY)
	{
		for (int i = 0; i < Entity::entity_collection_list.size(); i++)
		{
			Entity* e = Entity::entity_collection_list.at(i);
			EButton* b = brick_button.at(i);

			float min_gabarite_x = 0;
			float min_gabarite_y = 0;

			float max_gabarite_x = -10000.0f;
			float max_gabarite_y = -10000.0f;

			for (ESprite* spr : e->sprite_list)
			{
				for (int j = 0; j< spr->sprite_struct_list.size(); j++)
				{
					if (*spr->sprite_struct_list.at(j)->offset_x < min_gabarite_x) { min_gabarite_x = *spr->sprite_struct_list.at(j)->offset_x; }
					if (*spr->sprite_struct_list.at(j)->offset_y < min_gabarite_y) { min_gabarite_y = *spr->sprite_struct_list.at(j)->offset_y; }

					if (*spr->sprite_struct_list.at(j)->offset_x + *spr->sprite_struct_list.at(j)->gabarite->size_x > max_gabarite_x) { max_gabarite_x = *spr->sprite_struct_list.at(j)->offset_x + *spr->sprite_struct_list.at(j)->gabarite->size_x; }
					if (*spr->sprite_struct_list.at(j)->offset_y + *spr->sprite_struct_list.at(j)->gabarite->size_y > max_gabarite_y) { max_gabarite_y = *spr->sprite_struct_list.at(j)->offset_y + *spr->sprite_struct_list.at(j)->gabarite->size_y; }
				}
			}

			float total_size_x = abs(min_gabarite_x) + max_gabarite_x;
			float total_size_y = abs(min_gabarite_y) + max_gabarite_y;

			float resizer_horizontal = b->button_size_x / total_size_x;
			float resizer_vertical = b->button_size_y / total_size_y;

			float resize = 1.0;

			

			if (resizer_horizontal < resizer_vertical)
			{resize = resizer_horizontal;}
			else
			{resize = resizer_vertical;}

			if (resize > 1.0) { resize = 1.0f; }

			float sprite_image_offset_x = (b->button_size_x - (total_size_x  * resize)) / 2.0f;
			sprite_image_offset_x += abs(min_gabarite_x * resize);

			EGraphicCore::batch->setcolor(EColor::COLOR_WHITE);

			for (ESprite* spr : e->sprite_list)
			{
					EGraphicCore::batch->draw_gabarite
					(
						b->master_position_x + *spr->sprite_struct_list.at(0)->offset_x * resize + sprite_image_offset_x,
						b->master_position_y + *spr->sprite_struct_list.at(0)->offset_y * resize - min_gabarite_y * resize,
						*spr->sprite_struct_list.at(0)->gabarite->size_x * resize,
						*spr->sprite_struct_list.at(0)->gabarite->size_y * resize,
						spr->sprite_struct_list.at(0)->gabarite
					);
			}

		}
	}
}

void EWindowSearchBrick::update_search(EButton* _b)
{
	float xx = 0.0f;
	float yy = 0.0f;

	int new_data_id = 0;

	if (search_mode == SearchMode::SEARCH_TEXTURE)
	{
		for (int i = 0; i < brick_button.size(); i++)
		{
			brick_button.at(i)->have_icon = true;
			brick_button.at(i)->gabarite = list_of_textures.at(i);

			brick_button.at(i)->description_text = brick_button.at(i)->gabarite->name;
			brick_button.at(i)->data_string = list_of_textures_names.at(i);

			//brick_button.at(i)->action_on_left_click = &EBA::action_set_sprite_texture_for_autobuilding;
		}
	}

	if (search_mode == SearchMode::SEARCH_ENTITY)
	{
		for (int i = 0; i < brick_button.size(); i++)
		{
			brick_button.at(i)->have_icon = false;

			//brick_button.at(i)->action_on_left_click = &EBA::action_add_new_entity_from_collection;
		}
	}

		for (int i = 0; i < brick_button.size(); i++)
		{
			//std::cout << "gabarite [" << i << "] name is " << EGraphicCore::gabarite_list.at(i)->name << std::endl;

			if (EString::is_contain(brick_button.at(i)->data_string, _b->text))
			{
				brick_button.at(i)->is_active = true;

				xx += 85.0f;
				if (xx + brick_button.at(i)->button_size_x > window_size_x)
				{
					xx = 0;
					yy -= 85.0f;
				}

				brick_button.at(i)->button_x = 15.0f + xx;
				brick_button.at(i)->button_y = -50.0f + yy;
				brick_button.at(i)->data_id = new_data_id;

				new_data_id++;
			}
			else
			{
				brick_button.at(i)->is_active = false;
			}
		}
}




