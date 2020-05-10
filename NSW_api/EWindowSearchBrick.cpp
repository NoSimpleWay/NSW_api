#include "EWindowSearchBrick.h"

# define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <fstream>
#include <iostream>
#include <experimental/filesystem>
#include "EButtonActionSetSpriteTexture.h"
#include "EBA.h"
namespace fs = std::experimental::filesystem;

EWindowSearchBrick::EWindowSearchBrick()
{

	for (auto& p : fs::directory_iterator("data/textures"))
		std::cout << p << '\n';

	window_size_x = 700.0f;
	window_size_y = 800.0f;

	EButton* but = new EButton(15.0f, -15.0f, 300.0f, 30.0f);
	but->master_window = this;
	but->input_auto_clear_text = true;
	but->have_input_mode = true;
	but->is_input_mode_active = true;
	but->outclick_protection = true;

	but->action_on_input = &EBA::action_input_search_brick;

	but->position_mode_x = Enums::MID;
	but->position_mode_y = Enums::UP;

	link_to_input = but;
	button_list.push_back(but);

	float xx = 0;
	float yy = 0;

	//for (EGabarite* g: EGraphicCore::gabarite_list)
	for (auto& p : fs::directory_iterator("data/textures"))
	{
		

		but = new EButton(15.0f + xx, -50.0f + yy, 50.0f, 50.0f);
		but->master_window = this;

		but->position_mode_x = Enums::LEFT;
		but->position_mode_y = Enums::UP;
		but->have_icon = true;
		but->have_description = true;
		but->have_rama = true;

		//std::cout << "try load texture: " << p.path().filename().u8string() << std::endl;

		but->gabarite = ETextureAtlas::put_texture_to_atlas(p.path().u8string(), EWindow::default_texture_atlas);
		but->data_string = p.path().filename().u8string();//texture path
		but->description_text = p.path().filename().u8string();

		//but->button_action_press = new EButtonActionSetSpriteTexture();
		but->action_on_left_click = &EBA::action_set_sprite_texture;

		brick_button.push_back(but);
		button_list.push_back(but);

		xx += 55.0f;
		if (xx + but->button_size_x > window_size_x)
		{
			xx = 0;
			yy -= 50.0f;
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
			//std::cout << "gabarite [" << i << "] name is " << EGraphicCore::gabarite_list.at(i)->name << std::endl;

			if (EString::is_contain(brick_button.at(i)->data_string, _b->text))
			{
				brick_button.at(i)->is_active = true;

				xx += 55.0f;
				if (xx + brick_button.at(i)->button_size_x > window_size_x)
				{
					xx = 0;
					yy -= 50.0f;
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
}



