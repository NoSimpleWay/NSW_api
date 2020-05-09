#include "EWindowEditor.h"
#include "EButtonActionSetActiveSprite.h"
#include "EButtonActionAddNewSprite.h"
#include "EBA.h"

EWindowEditor::EWindowEditor()
{
	EButton* but;
	for (int i = 0; i < 10; i++)
	{
		but = new EButton(-150.0f, i * -65.0f, 100.0f, 60.0f);
		but->master_window = this;
		but->is_active = true;
		but->have_description = true;
		but->have_icon = true;
		but->have_rama = true;

		but->position_mode_x = Enums::PositionMode::RIGHT;
		but->position_mode_y = Enums::PositionMode::UP;

		but->data_id = i;
		//but->button_action_press = new EButtonActionSetActiveSprite();
		but->action_on_left_click = &EBA::action_select_sprite;
		//but->action_on_right_click = &EBA::action_set_as_remove_button;
		but->can_be_removed = true;

		button_list.push_back(but);
		sprite_button_list.push_back(but);
	}

	  ////////////////////////////////////////////////
	 /////	new sprite button		////////////////
	///////////////////////////////////////////////
	but = new EButton(-10.0f, 0.0f, 20.0f, 20.0f);
	but->master_window = this;
	but->have_description = true;
	but->have_icon = true;
	but->have_rama = true;

	but->position_mode_x = Enums::PositionMode::RIGHT;
	but->position_mode_y = Enums::PositionMode::UP;
	but->text = "+";

	//but->button_action_press = new EButtonActionAddNewSprite();
	//but->set_left_click_action(EBA::action_add_new_sprite);
	but->action_on_left_click = &EBA::action_add_new_sprite;

	link_to_add_new_sprite_button = but;
	button_list.push_back(but);

	but = new EButton(10.0f, -10.0f, 64.0f, 16.0f);
	but->master_window = this;
	button_list.push_back(but);
	but->text = "save";
	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::UP;
	but->action_on_left_click = &EBA::action_save_map;

	but = new EButton(90.0f, -10.0f, 64.0f, 16.0f);
	but->master_window = this;
	button_list.push_back(but);
	but->text = "load";
	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::UP;
	but->action_on_left_click = &EBA::action_load_map;


	//

	align_x = Enums::PositionMode::RIGHT;
	align_y = Enums::PositionMode::UP;

	window_size_x = 300.0f;
	window_size_y = 600.0f;

	//default_resize_event();
}

EWindowEditor::~EWindowEditor()
{
}


void EWindowEditor::update(float _d)
{
	for (int i = 0; i < sprite_button_list.size(); i++)
	{
		if (sprite_button_list.at(i)->need_remove)
		{
			sprite_button_list.erase(sprite_button_list.begin() + i);

			selected_entity->sprite_list.erase(selected_entity->sprite_list.begin() + i);
		}
	}

}

void EWindowEditor::draw(float _d)
{
}

void EWindowEditor::draw_interface(float _d)
{
}

void EWindowEditor::update_sprite_buttons()
{
	for (EButton* b : sprite_button_list)
	{
		b->is_active = false;
	}

	float yy = 0.0f;

	if (selected_entity != NULL)
	{
		for (int i = 0; i < selected_entity->sprite_list.size(); i++)
		{
			sprite_button_list.at(i)->button_y = yy;
			sprite_button_list.at(i)->is_active = true;
			sprite_button_list.at(i)->description_text = selected_entity->sprite_list.at(i)->gabarite.at(0)->name;
			sprite_button_list.at(i)->gabarite = selected_entity->sprite_list.at(i)->gabarite.at(0);

			yy -= sprite_button_list.at(i)->button_size_y - 10.0f;
		}
	}

	link_to_add_new_sprite_button->button_x = sprite_button_list.at(selected_sprite_id)->button_x + link_to_add_new_sprite_button->button_size_x + 10.0f;
	link_to_add_new_sprite_button->button_y = sprite_button_list.at(selected_sprite_id)->button_y - 10.0f;
	
}
