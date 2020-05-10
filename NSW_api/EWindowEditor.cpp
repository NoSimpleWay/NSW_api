#include "EWindowEditor.h"
#include "EWindowTest.h"
#include "EButtonActionSetActiveSprite.h"
#include "EButtonActionAddNewSprite.h"
#include "EBA.h"

EWindowEditor::EWindowEditor()
{
	EButton* but;
	for (int i = 0; i < 10; i++)
	{
		but = new EButton(-300.0f, i * -85.0f - 10.0f, 100.0f, 60.0f);
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

		if (i == 0) { selected_sprite_button = but; }
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

		  ////////////////////////////////////////////////
	 /////	move sprite up button		////////////////
	///////////////////////////////////////////////
	but = new EButton(0.0f, 0.0f, 30.0f, 20.0f);
	but->master_button = link_to_add_new_sprite_button;
	but->master_window = this;
	but->have_rama = true;

	but->master_position = Enums::PositionMaster::BUTTON;
	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::UP;
	but->text = "up";

	but->action_on_left_click = &EBA::action_move_sprite_up;

	button_list.push_back(but);

	  ////////////////////////////////////////////////
	 /////	select texture for sprite		////////////////
	///////////////////////////////////////////////
	but = new EButton(100.0f, 0.0f, 30.0f, 20.0f);
	but->master_button = link_to_add_new_sprite_button;
	but->master_window = this;
	but->have_rama = true;

	but->master_position = Enums::PositionMaster::BUTTON;
	but->position_mode_x = Enums::PositionMode::RIGHT;
	but->position_mode_y = Enums::PositionMode::UP;
	but->text = "change";

	but->action_on_left_click = &EBA::action_open_select_texture_window;

	button_list.push_back(but);


	////////////////////////////////////////////////
/////	move sprite down button		////////////////
///////////////////////////////////////////////
	but = new EButton(0.0f, 0.0f, 30.0f, 20.0f);
	but->master_button = link_to_add_new_sprite_button;
	but->master_window = this;
	but->have_rama = true;

	but->master_position = Enums::PositionMaster::BUTTON;
	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::DOWN;
	but->text = "down";

	but->action_on_left_click = &EBA::action_move_sprite_down;

	button_list.push_back(but);


	//save map
	but = new EButton(10.0f, -10.0f, 64.0f, 16.0f);
	but->master_window = this;
	button_list.push_back(but);
	but->text = "save";
	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::UP;
	but->action_on_left_click = &EBA::action_save_map;

	//load map
	but = new EButton(90.0f, -10.0f, 64.0f, 16.0f);
	but->master_window = this;
	button_list.push_back(but);
	but->text = "load";
	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::UP;
	but->action_on_left_click = &EBA::action_load_map;

	//edd new entity
	but = new EButton(165.0f, -10.0f, 150.0f, 16.0f);
	but->master_window = this;
	button_list.push_back(but);
	but->text = "add new entity";
	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::UP;
	but->action_on_left_click = &EBA::action_add_new_entity;





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
	bool any_remove = false;

	bool button_overlap = false;

	for (EButton* b : button_list)
	{
		if (b->is_overlap())
		{
			button_overlap = true; break;
		}
	}

	if ((EWindow::LMB)&(EButton::top_window_id == id)&(!button_overlap))
	{
		int target_cluster_left = EMath::clamp_value_int((int)((EWindow::mouse_x + EWindow::window_test->game_camera->position_x - EGraphicCore::SCR_WIDTH / 2.0f) / ECluster::CLUSTER_SIZE), 0, ECluster::CLUSTER_DIM - 1);
		int target_cluster_right = EMath::clamp_value_int((int)((EWindow::mouse_x + EWindow::window_test->game_camera->position_x + EGraphicCore::SCR_WIDTH / 2.0f) / ECluster::CLUSTER_SIZE), 0, ECluster::CLUSTER_DIM - 1);
		
		int target_cluster_up = EMath::clamp_value_int((int)((EWindow::mouse_y + EWindow::window_test->game_camera->position_y + EGraphicCore::SCR_HEIGHT / 2.0f) / ECluster::CLUSTER_SIZE), 0, ECluster::CLUSTER_DIM - 1);
		int target_cluster_down = EMath::clamp_value_int((int)((EWindow::mouse_y + EWindow::window_test->game_camera->position_y - EGraphicCore::SCR_HEIGHT / 2.0f) / ECluster::CLUSTER_SIZE), 0, ECluster::CLUSTER_DIM - 1);

		Entity* nearest_entity = NULL;

		float min_dst = 9999999.0f;

		for (int j = 0; j < ECluster::CLUSTER_DIM; j++)
		for (int i = 0; i < ECluster::CLUSTER_DIM; i++)
		for (Entity* e:ECluster::clusters[j][i]->entity_list)
		{

			float dst_x = (EWindow::mouse_x + EWindow::window_test->game_camera->position_x - EGraphicCore::SCR_WIDTH / 2.0f) - *e->position_x;
			float dst_y = (EWindow::mouse_y + EWindow::window_test->game_camera->position_y - EGraphicCore::SCR_HEIGHT / 2.0f) - *e->position_y;

			if (dst_x * dst_x + dst_y * dst_y < min_dst)
			{
				nearest_entity = e;
				min_dst = dst_x * dst_x + dst_y * dst_y;
			}



		}

		selected_entity = nearest_entity;
		update_sprite_buttons();
	}

	for (int i = 0; i < sprite_button_list.size(); i++)
	{
		if (sprite_button_list.at(i)->need_remove)
		{
			sprite_button_list.erase(sprite_button_list.begin() + i);

			selected_entity->sprite_list.erase(selected_entity->sprite_list.begin() + i);

			any_remove = true;
		}
	}

	if (any_remove)
	{
		EWindow::window_editor->update_sprite_buttons();
	}

	if (glfwGetKey(EWindow::main_window, GLFW_KEY_X) == GLFW_PRESS)
	{
		if (!started_sprite_move)
		{
			saved_pos_x = real_mouse_x;
			saved_pos_y = real_mouse_y;
		}

		started_sprite_move = true;

		if (selected_entity != NULL)
		{
			float mul = 1.0f;
			if
			(
				(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				||
				(glfwGetKey(EWindow::main_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
			)
			{
				mul = 0.1f;
			}

			if (!selected_entity->sprite_list.empty())
			{
				selected_entity->sprite_list.at(selected_sprite_id)->offset_x.at(0) += mouse_speed_x * mul;
				selected_entity->sprite_list.at(selected_sprite_id)->offset_y.at(0) += mouse_speed_y * mul;
			}

			
			SetCursorPos(saved_pos_x, saved_pos_y);
			prev_mouse_x = saved_pos_x;
			prev_mouse_y = saved_pos_y;
			//EWindow::push_cursor(EWindow::mouse_speed_x, EWindow::mouse_speed_y);
		}
	}
	else
	{
		if (started_sprite_move)
		{
			//selected_entity->sprite_list.at(selected_sprite_id)->offset_x.at(0) = round(selected_entity->sprite_list.at(selected_sprite_id)->offset_x.at(0));
			//selected_entity->sprite_list.at(selected_sprite_id)->offset_y.at(0) = round(selected_entity->sprite_list.at(selected_sprite_id)->offset_y.at(0));

			saved_pos_x = -1;
			saved_pos_y = -1;

		}

		started_sprite_move = false;
	}

	if (glfwGetKey(EWindow::main_window, GLFW_KEY_C) == GLFW_PRESS)
	{
		if (!started_entity_move)
		{
			saved_pos_x = real_mouse_x;
			saved_pos_y = real_mouse_y;
		}

		started_entity_move = true;

		if (selected_entity != NULL)
		{
			float mul = 1.0f;
			if
				(
				(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				||
				(glfwGetKey(EWindow::main_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
				)
			{
				mul = 0.1f;
			}

			*selected_entity->position_x += EWindow::mouse_speed_x * mul;
			*selected_entity->position_y += EWindow::mouse_speed_y * mul;


			SetCursorPos(saved_pos_x, saved_pos_y);
			prev_mouse_x = saved_pos_x;
			prev_mouse_y = saved_pos_y;
			//EWindow::push_cursor(EWindow::mouse_speed_x, EWindow::mouse_speed_y);
		}
	}
	else
	{
		started_entity_move = false;
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

	int id = 0;
	float yy = -10.0f;

	if (selected_entity != NULL)
	{
		for (int i = 0; i < selected_entity->sprite_list.size(); i++)
		{
			sprite_button_list.at(i)->button_y = yy;
			sprite_button_list.at(i)->is_active = true;
			sprite_button_list.at(i)->description_text = selected_entity->sprite_list.at(i)->gabarite.at(0)->name;
			sprite_button_list.at(i)->gabarite = selected_entity->sprite_list.at(i)->gabarite.at(0);

			yy -= sprite_button_list.at(i)->button_size_y + 10.0f;

			if (i == selected_sprite_id)
			{
				sprite_button_list.at(i)->rama_color->set_color(EColor::COLOR_ORANGE);
				sprite_button_list.at(i)->rama_thikness = 5.0f;
			}
			else
			{
				sprite_button_list.at(i)->rama_color->set_color(EColor::COLOR_BLACK);
				sprite_button_list.at(i)->rama_thikness = 2.0f;
			}
			
			sprite_button_list.at(i)->data_id = i;
		}
	}

	link_to_add_new_sprite_button->button_x = sprite_button_list.at(selected_sprite_id)->button_x + link_to_add_new_sprite_button->button_size_x + 10.0f;
	link_to_add_new_sprite_button->button_y = sprite_button_list.at(selected_sprite_id)->button_y - 20.0f;
	
}
