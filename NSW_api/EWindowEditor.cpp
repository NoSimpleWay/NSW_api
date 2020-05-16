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
		but = new EButton(-300.0f, i * -85.0f - 10.0f, 200.0f, 60.0f);
		but->master_window = this;
		but->is_active = true;
		but->have_description = true;
		but->have_icon = true;
		but->have_rama = true;
		but->icon_adaptation = true;

		but->position_mode_x = Enums::PositionMode::RIGHT;
		but->position_mode_y = Enums::PositionMode::UP;

		but->data_id = i;
		//but->button_action_press = new EButtonActionSetActiveSprite();
		but->action_on_left_click = &EBA::action_select_sprite;
		//but->action_on_right_click = &EBA::action_set_as_remove_button;
		but->can_be_removed = true;

		button_list.push_back(but);
		sprite_button_list.push_back(but);
		link_to_sprite_editor_group.push_back(but);

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
	link_to_sprite_editor_group.push_back(but);

		  ////////////////////////////////////////////////
	 /////	move sprite up button		////////////////
	///////////////////////////////////////////////
	but = new EButton(0.0f, 5.0f, 40.0f, 20.0f);
	but->master_button = link_to_add_new_sprite_button;
	but->master_window = this;
	but->have_rama = true;

	but->master_position = Enums::PositionMaster::BUTTON;
	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::UP;
	but->text = "up";

	but->action_on_left_click = &EBA::action_move_sprite_up;

	button_list.push_back(but);
	link_to_sprite_editor_group.push_back(but);

	  ////////////////////////////////////////////////
	 /////	select texture for sprite		////////////////
	///////////////////////////////////////////////
	but = new EButton(80.0f, 0.0f, 30.0f, 20.0f);
	but->master_button = link_to_add_new_sprite_button;
	but->master_window = this;
	but->have_rama = true;

	but->master_position = Enums::PositionMaster::BUTTON;
	but->position_mode_x = Enums::PositionMode::RIGHT;
	but->position_mode_y = Enums::PositionMode::MID;
	but->text = "change";

	but->action_on_left_click = &EBA::action_open_select_texture_window;

	button_list.push_back(but);
	link_to_sprite_editor_group.push_back(but);


	////////////////////////////////////////////////
/////	move sprite down button		////////////////
///////////////////////////////////////////////
	but = new EButton(0.0f, -5.0f, 40.0f, 20.0f);
	but->master_button = link_to_add_new_sprite_button;
	but->master_window = this;
	but->have_rama = true;

	but->master_position = Enums::PositionMaster::BUTTON;
	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::DOWN;
	but->text = "down";

	but->action_on_left_click = &EBA::action_move_sprite_down;

	button_list.push_back(but);
	link_to_sprite_editor_group.push_back(but);


	////////////////////////////////////////////////
/////	set 4 textures mode		////////////////
///////////////////////////////////////////////
	but = new EButton(0.0f, -40.0f, 20.0f, 20.0f);
	but->master_button = link_to_add_new_sprite_button;
	but->master_window = this;
	but->have_rama = true;

	but->master_position = Enums::PositionMaster::BUTTON;
	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::DOWN;
	but->text = "4";

	but->action_on_left_click = &EBA::action_set_sprite_mode_4;

	button_list.push_back(but);
	link_to_sprite_editor_group.push_back(but);
	link_to_is_rotate_by_move_button = but;

	////////////////////////////////////////////////
/////	set wall mode		////////////////
///////////////////////////////////////////////
	but = new EButton(3.0f, 00.0f, 20.0f, 20.0f);
	but->master_button = link_to_is_rotate_by_move_button;
	but->master_window = this;
	but->have_rama = true;

	but->master_position = Enums::PositionMaster::BUTTON;
	but->position_mode_x = Enums::PositionMode::SUPER_RIGHT;
	but->position_mode_y = Enums::PositionMode::MID;
	but->text = "w";

	but->action_on_left_click = &EBA::action_set_sprite_mode_wall;

	button_list.push_back(but);
	link_to_sprite_editor_group.push_back(but);
	link_to_is_wall_mode = but;


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
	but->data_string = "test/map.txt";

	//add new entity from collection (open brick search window)
	but = new EButton(165.0f, -10.0f, 150.0f, 16.0f);
	but->master_window = this;
	button_list.push_back(but);
	but->text = "entity from collection";
	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::UP;
	but->action_on_left_click = &EBA::action_open_select_entity_collection_window;

	//add new entity
	but = new EButton(165.0f, -30.0f, 150.0f, 16.0f);
	but->master_window = this;
	button_list.push_back(but);
	but->text = "new entity";
	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::UP;
	but->action_on_left_click = &EBA::action_add_new_entity;

	//add entity to collection
	but = new EButton(330.0f, -10.0f, 150.0f, 16.0f);
	but->master_window = this;
	button_list.push_back(but);
	but->text = "add entity to collection";
	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::UP;
	but->action_on_left_click = &EBA::action_save_entity_to_collection;

	//entity properities
	but = new EButton(-30.0f, 300.0f, 150.0f, 16.0f);
	but->master_window = this;
	button_list.push_back(but);
	link_to_entity_propeties_button = but;
	but->text = "entity properties";
	but->position_mode_x = Enums::PositionMode::RIGHT;
	but->position_mode_y = Enums::PositionMode::DOWN;
	
	//entity mass
	but = new EButton(0.0f, -3.0f, 150.0f, 16.0f);
	but->master_position = Enums::PositionMaster::BUTTON;
	but->master_button = link_to_entity_propeties_button;
	but->master_window = this;
	but->action_on_input_finish = &EBA::action_set_mass;

	button_list.push_back(but);
	link_to_entity_mass_button = but;
	but->input_only_numbers = true;

	but->text = "0";
	but->input_hint = "mass";
	but->have_input_mode = true;

	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::DOWN;

	//entity inmovable
	but = new EButton(0.0f, -3.0f, 150.0f, 16.0f);
	but->master_position = Enums::PositionMaster::BUTTON;
	but->master_button = link_to_entity_mass_button;
	but->master_window = this;
	but->action_on_left_click = &EBA::action_set_inmovable;

	button_list.push_back(but);
	link_to_entity_inmovable_button = but;

	but->text = "inmovable";
	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::DOWN;


	//controlled by player
	but = new EButton(0.0f, -3.0f, 150.0f, 16.0f);
	but->master_position = Enums::PositionMaster::BUTTON;
	but->master_button = link_to_entity_inmovable_button;
	but->master_window = this;
	but->action_on_left_click = &EBA::action_set_controlled_by_player;

	button_list.push_back(but);
	link_to_entity_controlled_by_player_button = but;

	but->text = "controlled by player";
	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::DOWN;

	//controlled by AI
	but = new EButton(0.0f, -3.0f, 150.0f, 16.0f);
	but->master_position = Enums::PositionMaster::BUTTON;
	but->master_button = link_to_entity_controlled_by_player_button;
	but->master_window = this;
	but->action_on_left_click = &EBA::action_set_controlled_by_AI;

	button_list.push_back(but);
	link_to_entity_controlled_by_AI_button = but;

	but->text = "controled by AI";
	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::DOWN;

	//controlled by AI
	but = new EButton(0.0f, -3.0f, 150.0f, 16.0f);
	
	but->master_button = link_to_entity_controlled_by_AI_button;
	link_to_set_camera_target_button = but;

	but->master_position = Enums::PositionMaster::BUTTON;

	but->master_window = this;
	but->action_on_left_click = &EBA::action_set_camera_target;

	button_list.push_back(but);
	

	but->text = "set as camera target";
	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::DOWN;
	
	//but->action_on_left_click = &EBA::action_save_entity_to_collection;

	for (int i = 0; i < 8; i++)
	{
		//edd new entity
		but = new EButton(0.0f + i * 42.0f, -10.0f, 40.0f, 40.0f);
		but->master_window = this;
		but->master_button = sprite_button_list.at(0);
		but->have_icon = true;
		but->gabarite = EGraphicCore::gabarite_white_pixel;
		but->master_position = Enums::BUTTON;
		but->have_rama = true;

		but->data_id = i;

		button_list.push_back(but);

		but->text = "";
		but->position_mode_x = Enums::PositionMode::LEFT;
		but->position_mode_y = Enums::PositionMode::DOWN;
		but->action_on_left_click = &EBA::action_select_frame;

		link_to_sprite_frame.push_back(but);
		link_to_sprite_editor_group.push_back(but);
	}



	//

	align_x = Enums::PositionMode::RIGHT;
	align_y = Enums::PositionMode::UP;

	window_size_x = 300.0f;
	window_size_y = 600.0f;

	update_sprite_buttons();

	//default_resize_event();
}

EWindowEditor::~EWindowEditor()
{
}


void EWindowEditor::update(float _d)
{
	sprite_flash_cooldown -= _d* 2.0f;
	if (sprite_flash_cooldown < 0)
	{
		sprite_flash_cooldown += 1.0f;
	}
	bool any_remove = false;

	bool button_overlap = false;

	for (EButton* b : button_list)
	{
		if (b->is_overlap())
		{
			button_overlap = true; break;
		}
	}

	if (glfwGetKey(EWindow::main_window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		float min_y = 999999.0f;

		for (Entity* e : selected_entity_list)
		{
			if (*e->position_y < min_y) { min_y = *e->position_y; }
		}

		for (Entity* e : selected_entity_list)
		{
			*e->position_y = min_y;
		}
	}

	if (glfwGetKey(EWindow::main_window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		if (!rama_start_selection)
		{
			rama_start_selection = true;

			rama_selector_start_x = ECamera::get_world_position_x(EWindow::window_test->game_camera);
			rama_selector_start_y = ECamera::get_world_position_y(EWindow::window_test->game_camera);
		}
		else
		{
			rama_selector_end_x = ECamera::get_world_position_x(EWindow::window_test->game_camera);
			rama_selector_end_y = ECamera::get_world_position_y(EWindow::window_test->game_camera);
		}

		selected_entity = NULL;
		selected_entity_list.clear();

		for (int j = 0; j < ECluster::CLUSTER_DIM; j++)
		for (int i = 0; i < ECluster::CLUSTER_DIM; i++)
		for (Entity* e : ECluster::clusters[j][i]->entity_list)
		{
			if
			(
				(*e->position_x >= rama_selector_start_x - *e->collision_right)
				&
				(*e->position_x <= rama_selector_end_x + *e->collision_left)
				&
				(*e->position_y >= rama_selector_start_y - *e->collision_up)
				&
				(*e->position_y <= rama_selector_end_y + *e->collision_down)
			)
			{
				selected_entity_list.push_back(e);
			}
		}


	}
	else
	{
		if (rama_start_selection)
		{
			rama_start_selection = false;


		}
	}

	if (glfwGetKey(EWindow::main_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		editor_mode = EditMode::SelectEntities;
		EWindow::button_main_group_pressed = true;
		update_sprite_buttons();
	}

	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_COMMA) == GLFW_PRESS) & (!EWindow::button_main_group_pressed) & (editor_mode == EditMode::EditSprites))
	{
		EWindow::button_main_group_pressed = true;

		selected_entity->sprite_list.at(selected_sprite_id)->copies.at(selected_frame_id)--;
		
		if (selected_entity->sprite_list.at(selected_sprite_id)->copies.at(selected_frame_id) < 1)
		{
			selected_entity->sprite_list.at(selected_sprite_id)->copies.at(selected_frame_id) = 1;
		}
		//selected_entity
	}

	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_PERIOD) == GLFW_PRESS) & (!EWindow::button_main_group_pressed) & (editor_mode == EditMode::EditSprites))
	{
		EWindow::button_main_group_pressed = true;

		selected_entity->sprite_list.at(selected_sprite_id)->copies.at(selected_frame_id)++;
		
		if (selected_entity->sprite_list.at(selected_sprite_id)->copies.at(selected_frame_id) > 100)
		{
			selected_entity->sprite_list.at(selected_sprite_id)->copies.at(selected_frame_id) = 100;
		}
		//selected_entity
	}

	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_E) == GLFW_PRESS) & (!EWindow::button_main_group_pressed) & (selected_entity != NULL))
	{
		editor_mode = EditMode::EditSprites;
		EWindow::button_main_group_pressed = true;
		update_sprite_buttons();

	}

	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_DELETE) == GLFW_PRESS) & (!EWindow::button_main_group_pressed) & (selected_entity != NULL))
	{
		EWindow::button_main_group_pressed = true;
		*selected_entity->need_remove = true;
		selected_entity = NULL;

	}

	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_V) == GLFW_PRESS) & (!EWindow::button_main_group_pressed) & (selected_entity != NULL))
	{
		EWindow::button_main_group_pressed = true;
		
		clone_entity(selected_entity);

	}

	if ((EWindow::LMB) & (EButton::top_window_id == id) & (!button_overlap) & (!EWindow::button_pressed) & (editor_mode == EditMode::EditSprites) & (selected_entity != NULL))
	{
		float xx = ECamera::get_world_position_x(EWindow::window_test->game_camera);
		float yy = ECamera::get_world_position_y(EWindow::window_test->game_camera);

		float min_dist = 9999.0f;
		int nearest_sprite = 0;

		if (selected_entity != NULL)
		{
			for (int i = 0; i < selected_entity->sprite_list.size(); i++)
			{
				ESprite* sp = selected_entity->sprite_list.at(i);

				float dst_x = *selected_entity->position_x + sp->offset_x.at(0) - xx;
				float dst_y = *selected_entity->position_y + sp->offset_y.at(0) - yy;
				float dst = dst_x * dst_x + dst_y * dst_y;

				if (dst < min_dist)
				{
					min_dist = dst;
					nearest_sprite = i;
				}
			}
		}

		selected_sprite_id = nearest_sprite;
	}

	if ((EWindow::LMB)&(EButton::top_window_id == id)&(!button_overlap)&(!EWindow::button_pressed)&(editor_mode == EditMode::SelectEntities))
	{

		selected_entity_list.clear();
		int target_cluster_left = EMath::clamp_value_int((int)( ECamera::get_world_position_x(EWindow::window_test->game_camera)/ ECluster::CLUSTER_SIZE) - 1, 0, ECluster::CLUSTER_DIM - 1);
		int target_cluster_right = EMath::clamp_value_int((int)(ECamera::get_world_position_x(EWindow::window_test->game_camera) / ECluster::CLUSTER_SIZE) + 1, 0, ECluster::CLUSTER_DIM - 1);
		
		int target_cluster_up = EMath::clamp_value_int((int)(ECamera::get_world_position_y(EWindow::window_test->game_camera) / ECluster::CLUSTER_SIZE) + 1, 0, ECluster::CLUSTER_DIM - 1);
		int target_cluster_down = EMath::clamp_value_int((int)(ECamera::get_world_position_y(EWindow::window_test->game_camera) / ECluster::CLUSTER_SIZE) - 1, 0, ECluster::CLUSTER_DIM - 1);

		//EGraphicCore::batch->setcolor(EColor::COLOR_PINK);
		//EGraphicCore::batch->draw_gabarite(target_cluster_left * ECluster::CLUSTER_SIZE, target_cluster_down * ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, ECluster::CLUSTER_SIZE, EGraphicCore::gabarite_white_pixel );

		Entity* nearest_entity = NULL;

		float min_dst = 9999999.0f;

		for (int j = 0; j < ECluster::CLUSTER_DIM; j++)
		for (int i = 0; i < ECluster::CLUSTER_DIM; i++)
		for (Entity* e:ECluster::clusters[j][i]->entity_list)
		{

			float dst_x = (ECamera::get_world_position_x(EWindow::window_test->game_camera)) - *e->position_x;
			float dst_y = (ECamera::get_world_position_y(EWindow::window_test->game_camera)) - *e->position_y;

			if (dst_x * dst_x + dst_y * dst_y < min_dst)
			{
				nearest_entity = e;
				min_dst = dst_x * dst_x + dst_y * dst_y;
			}



		}

		if (selected_entity != nearest_entity)
		{
			selected_sprite_id = 0;
			selected_frame_id = 0;
		}
		selected_entity = nearest_entity;
		update_on_entity_select();
		update_sprite_buttons();
	}

	for (int i = 0; i < sprite_button_list.size(); i++)
	{
		//EWindow::window_editor->selected_frame_id = 0;

		if (sprite_button_list.at(i)->need_remove)
		{
			//if (selected_sprite_id == i)
			{
				selected_sprite_id--;
				if (selected_sprite_id < 0)
				{
					selected_sprite_id = 0;
				}
			}

			//sprite_button_list.erase(sprite_button_list.begin() + i);
			//EWindow::window_editor->selected_frame_id = 0;
			selected_entity->sprite_list.erase(selected_entity->sprite_list.begin() + i);
			//EWindow::window_editor->selected_sprite_id = 0;

			any_remove = true;
			sprite_button_list.at(i)->need_remove = false;
		}

	}

	if (any_remove)
	{
		EWindow::window_editor->update_sprite_buttons();
	}

	if ((editor_mode == EditMode::EditSprites) & (selected_entity != NULL))
	{
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
					selected_entity->sprite_list.at(selected_sprite_id)->offset_x.at(EWindow::window_editor->selected_frame_id) += mouse_speed_x * mul;
					selected_entity->sprite_list.at(selected_sprite_id)->offset_y.at(EWindow::window_editor->selected_frame_id) += mouse_speed_y * mul;
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
				selected_entity->sprite_list.at(selected_sprite_id)->offset_x.at(0) = round(selected_entity->sprite_list.at(selected_sprite_id)->offset_x.at(0));
				selected_entity->sprite_list.at(selected_sprite_id)->offset_y.at(0) = round(selected_entity->sprite_list.at(selected_sprite_id)->offset_y.at(0));

				saved_pos_x = -1;
				saved_pos_y = -1;

			}

			started_sprite_move = false;
		}
	}

	if ((editor_mode == EditMode::SelectEntities) && (selected_entity != NULL))
	{
	
		if (!started_collision_move)
		{
			catched_collision_down = false;
			catched_collision_left = false;
			catched_collision_right = false;
			catched_collision_up = false;

			float xx= ECamera::get_world_position_x(EWindow::window_test->game_camera);
			float yy= ECamera::get_world_position_y(EWindow::window_test->game_camera);

			if
			(
				(xx >= *selected_entity->position_x - *selected_entity->collision_left - 20.0f)
				&
				(xx <= *selected_entity->position_x - *selected_entity->collision_left + 10.0f)
				&
				(yy <= *selected_entity->position_y + *selected_entity->collision_up + 20.0f)
				&
				(yy >= *selected_entity->position_y - *selected_entity->collision_down - 20.0f)
			)
			{catched_collision_left = true; }

			if
			(
				(xx >= *selected_entity->position_x - *selected_entity->collision_left - 20.0f)
				&
				(xx <= *selected_entity->position_x + *selected_entity->collision_right + 20.0f)
				&
				(yy <= *selected_entity->position_y + *selected_entity->collision_up + 20.0f)
				&
				(yy >= *selected_entity->position_y + *selected_entity->collision_up - 10.0f)
			)
			{catched_collision_up = true; }

			if
			(
				(xx <= *selected_entity->position_x + *selected_entity->collision_right + 20.0f)
				&
				(xx >= *selected_entity->position_x + *selected_entity->collision_right - 10.0f)
				&
				(yy <= *selected_entity->position_y + *selected_entity->collision_up + 20.0f)
				&
				(yy >= *selected_entity->position_y - *selected_entity->collision_down - 20.0f)
			)
			{catched_collision_right = true; }

			if
			(
				(xx >= *selected_entity->position_x - *selected_entity->collision_left - 20.0f)
				&
				(xx <= *selected_entity->position_x + *selected_entity->collision_right + 20.0f)
				&
				(yy >= *selected_entity->position_y - *selected_entity->collision_down - 20.0f)
				&
				(yy <= *selected_entity->position_y - *selected_entity->collision_down + 10.0f)
			)
			{catched_collision_down = true; }
		}
	

		if (glfwGetKey(EWindow::main_window, GLFW_KEY_X) == GLFW_PRESS)
		{
			if (!started_collision_move)
			{
				saved_pos_x = real_mouse_x;
				saved_pos_y = real_mouse_y;
			}

			started_collision_move = true;
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


			if (catched_collision_down)
			{
				*selected_entity->collision_down -= EWindow::mouse_speed_y * mul;
				*selected_entity->collision_down = EMath::clamp_value_float(*selected_entity->collision_down, 0.0f, 512.0f);
			}

			if (catched_collision_up)
			{
				*selected_entity->collision_up += EWindow::mouse_speed_y * mul;
				*selected_entity->collision_up = EMath::clamp_value_float(*selected_entity->collision_up, 0.0f, 512.0f);
			}

			if (catched_collision_left)
			{
				*selected_entity->collision_left -= EWindow::mouse_speed_x * mul;
				*selected_entity->collision_left = EMath::clamp_value_float(*selected_entity->collision_left, 0.0f, 512.0f);
			}

			if (catched_collision_right)
			{
				*selected_entity->collision_right += EWindow::mouse_speed_x * mul;
				*selected_entity->collision_right = EMath::clamp_value_float(*selected_entity->collision_right, 0.0f, 512.0f);
			}

			SetCursorPos(saved_pos_x, saved_pos_y);
			prev_mouse_x = saved_pos_x;
			prev_mouse_y = saved_pos_y;
		}
		else
		{
			started_collision_move = false;
		}
	}

	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_C) == GLFW_PRESS))
	{
		if (!started_entity_move)
		{
			saved_pos_x = real_mouse_x;
			saved_pos_y = real_mouse_y;
		}

		started_entity_move = true;

		
		
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

			if (selected_entity != NULL)
			{
				*selected_entity->position_x += EWindow::mouse_speed_x * mul;
				*selected_entity->position_y += EWindow::mouse_speed_y * mul;

				*selected_entity->need_change_cluster = true;
			}

			if (!selected_entity_list.empty())
			{
				for (Entity* e : selected_entity_list)
				{
					*e->position_x += EWindow::mouse_speed_x * mul;
					*e->position_y += EWindow::mouse_speed_y * mul;

					*e->need_change_cluster = true;
				}
			}

			SetCursorPos(saved_pos_x, saved_pos_y);
			prev_mouse_x = saved_pos_x;
			prev_mouse_y = saved_pos_y;
			//EWindow::push_cursor(EWindow::mouse_speed_x, EWindow::mouse_speed_y);
		
	}
	else
	{
		if (started_entity_move)
		{
			if (selected_entity != NULL)
			{
				*selected_entity->position_x = round(*selected_entity->position_x);
				*selected_entity->position_y = round(*selected_entity->position_y);
			}

			if (!selected_entity_list.empty())
			{
				for (Entity* e : selected_entity_list)
				{
					*e->position_x = round(*e->position_x);
					*e->position_y = round(*e->position_y);
				}
			}

		}
		started_entity_move = false;

		
		
	}

}

void EWindowEditor::clone_entity(Entity* _e)
{
	Entity* clone = new Entity();
	*clone->position_x = *_e->position_x;
	*clone->position_y = *_e->position_y;

	*clone->mass = *_e->mass;

	*clone->collision_down = *_e->collision_down;
	*clone->collision_left = *_e->collision_left;
	*clone->collision_right = *_e->collision_right;
	*clone->collision_up = *_e->collision_up;

	clone->controlled_by_ai = _e->controlled_by_ai;
	clone->controlled_by_player = _e->controlled_by_player;



	for (ESprite* spr : _e->sprite_list)
	{
		int id = 0;

		ESprite* clone_sprite = new ESprite();
		ESprite::clear_default_data(clone_sprite);

		clone->sprite_list.push_back(clone_sprite);

		*clone_sprite->rotate_by_move = *spr->rotate_by_move;
		*clone_sprite->rotate_by_target = *spr->rotate_by_target;

		*clone_sprite->wall_mode = *spr->wall_mode;

		for (EGabarite* g : spr->gabarite)
		{
			clone_sprite->gabarite.push_back(g);

			clone_sprite->offset_x.push_back(spr->offset_x.at(id));
			clone_sprite->offset_y.push_back(spr->offset_y.at(id));

			clone_sprite->copies.push_back(spr->copies.at(id));

			id++;
		}
	}

	*clone->position_x = round(EWindow::window_test->game_camera->position_x / EWindow::window_test->game_camera->zoom);
	*clone->position_y = round(EWindow::window_test->game_camera->position_y / EWindow::window_test->game_camera->zoom);

	selected_entity = clone;

	EWindow::window_editor->selected_frame_id = 0;
	EWindow::window_editor->selected_sprite_id = 0;

	ECluster::put_entity(clone);
}

void EWindowEditor::draw(float _d)
{
	EGraphicCore::batch->reinit();
	EGraphicCore::batch->draw_call();

	EGraphicCore::batch->reset();
	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3((EGraphicCore::SCR_WIDTH / 2.0f - EWindow::window_test->game_camera->position_x) * EGraphicCore::correction_x - 1, (EGraphicCore::SCR_HEIGHT / 2.0f - EWindow::window_test->game_camera->position_y) * EGraphicCore::correction_y - 1, 0.0f));
	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x * EWindow::window_test->game_camera->zoom, EGraphicCore::correction_y * EWindow::window_test->game_camera->zoom, 1));

	transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));


	
	//indicate selected collision gabarites
	if ((editor_mode == EditMode::SelectEntities) & (selected_entity != NULL))
	{
		EGraphicCore::batch->setcolor(EColor::COLOR_BLUE);

		if (catched_collision_left)
		{
			EGraphicCore::batch->draw_rama
			(
			*selected_entity->position_x		- *selected_entity->collision_left - 3.0f,
			*selected_entity->position_y		- *selected_entity->collision_down - 3.0f,
			6.0f,
			*selected_entity->collision_down	+ *selected_entity->collision_up + 3.0f,
			3.0f,
			EGraphicCore::gabarite_white_pixel
			);
		}

		if (catched_collision_up)
		{
			EGraphicCore::batch->draw_rama
			(
			*selected_entity->position_x		- *selected_entity->collision_left - 3.0f,
			*selected_entity->position_y		+ *selected_entity->collision_up - 3.0f,
			*selected_entity->collision_left + *selected_entity->collision_right + 3.0f,
			6.0f,
			3.0f,
			EGraphicCore::gabarite_white_pixel
			);
		}

		if (catched_collision_right)
		{
			EGraphicCore::batch->draw_rama
			(
			*selected_entity->position_x		+ *selected_entity->collision_right - 3.0f,
			*selected_entity->position_y		- *selected_entity->collision_down - 3.0f,
			6.0f,
			*selected_entity->collision_down	+ *selected_entity->collision_up + 3.0f,
			3.0f,
			EGraphicCore::gabarite_white_pixel
			);
		}

		if (catched_collision_down)
		{
			EGraphicCore::batch->draw_rama
			(
			*selected_entity->position_x		- *selected_entity->collision_left - 3.0f,
			*selected_entity->position_y		- *selected_entity->collision_down - 3.0f,
			*selected_entity->collision_left + *selected_entity->collision_right + 3.0f,
			6.0f,
			3.0f,
			EGraphicCore::gabarite_white_pixel
			);
		}
		
	}

	//rama selector
	if (rama_start_selection)
	{
		EGraphicCore::batch->setcolor(EColor::COLOR_RED);
		EGraphicCore::batch->draw_rama(rama_selector_start_x, rama_selector_start_y, rama_selector_end_x - rama_selector_start_x, rama_selector_end_y - rama_selector_start_y, 2.0f / EWindow::window_test->game_camera->zoom, EGraphicCore::gabarite_white_pixel);
	}
}

void EWindowEditor::draw_interface(float _d)
{
}

void EWindowEditor::selected_or_unselected_color(EButton* _b, bool _selected)
{
	if (_selected)
	{
		_b->have_rama = true;

		_b->bg_color->set_color_lum(EColor::COLOR_GREEN, 0.35f);
		_b->rama_color->set_color_lum(EColor::COLOR_GREEN, 0.85f);
		_b->text_color->set_color_lum(EColor::COLOR_GREEN, 0.85f);
	}
	else
	{
		_b->have_rama = false;

		_b->bg_color->set_color_alpha(EColor::COLOR_RED, 0.55f);
		//_b->rama_color->set_color_lum(EColor::COLOR_GREEN, 0.35f);
		_b->text_color->set_color_lum(EColor::COLOR_RED, 0.25f);
	}
}

void EWindowEditor::update_sprite_buttons()
{

	for (EButton* b : link_to_sprite_editor_group)
	{
		{b->is_active = editor_mode == EditMode::EditSprites;}
	}



	for (EButton* b : sprite_button_list)
	{
		b->is_active = false;
	}


	int id = 0;
	float yy = -10.0f;

	if ((editor_mode == EditMode::EditSprites) & (selected_entity != NULL))
	{
		selected_or_unselected_color(link_to_is_rotate_by_move_button, *selected_entity->sprite_list.at(selected_sprite_id)->rotate_by_move);
		selected_or_unselected_color(link_to_is_wall_mode, *selected_entity->sprite_list.at(selected_sprite_id)->wall_mode);

		if (selected_entity != NULL)
		{
			for (int i = 0; i < selected_entity->sprite_list.size(); i++)
			{
				sprite_button_list.at(i)->button_y = yy;
				sprite_button_list.at(i)->is_active = true;
				sprite_button_list.at(i)->description_text = selected_entity->sprite_list.at(i)->gabarite.at(0)->name;
				//sprite_button_list.at(i)->gabarite = selected_entity->sprite_list.at(i)->gabarite.at(0);

				yy -= sprite_button_list.at(i)->button_size_y + 10.0f;




				if (i == selected_sprite_id)
				{

					if (selected_frame_id >= selected_entity->sprite_list.at(i)->gabarite.size())
					{selected_frame_id = selected_entity->sprite_list.at(i)->gabarite.size() - 1;}

					sprite_button_list.at(i)->rama_color->set_color(EColor::COLOR_ORANGE);
					sprite_button_list.at(i)->rama_thikness = 5.0f;


					yy -= 50.0f;
					
					sprite_button_list.at(i)->gabarite = selected_entity->sprite_list.at(i)->gabarite.at(selected_frame_id);
				}
				else
				{
					sprite_button_list.at(i)->rama_color->set_color(EColor::COLOR_BLACK);
					sprite_button_list.at(i)->rama_thikness = 2.0f;

					std::cout << "vector size:" << sprite_button_list.size() << " id:" << i << std::endl;

					/*sprite_button_list.at(i)->gabarite
					=
					selected_entity->sprite_list.at(i)
					->gabarite.at(selected_frame_id);*/
					sprite_button_list.at(i)->gabarite = selected_entity->sprite_list.at(i)->gabarite.at(0);
				}

				sprite_button_list.at(i)->data_id = i;
			}

			
			for (EButton* b : link_to_sprite_frame)
			{
				b->master_button = sprite_button_list.at(selected_sprite_id);
			}

			int sid = 0;
			for (int i = 0; i < link_to_sprite_frame.size(); i++)
			{
				EButton* fr = link_to_sprite_frame.at(i);
				//std::cout << "process:" << z << std::endl;

				
				if (i < selected_entity->sprite_list.at(selected_sprite_id)->gabarite.size())
				{
					fr->is_active = true;

					fr->gabarite = selected_entity->sprite_list.at(selected_sprite_id)->gabarite.at(sid);

					sid++;
				}
				else
				{
					fr->is_active = false;
				}






				if (i == selected_frame_id)
				{
					fr->rama_thikness = 2.0f;
					fr->rama_color->set_color(EColor::COLOR_ORANGE);
				}
				else
				{
					fr->rama_thikness = 1.0f;
					fr->rama_color->set_color(EColor::COLOR_GRAY);
				}
			}
		}

		link_to_add_new_sprite_button->button_x = sprite_button_list.at(selected_sprite_id)->button_x + link_to_add_new_sprite_button->button_size_x + 10.0f;
		link_to_add_new_sprite_button->button_y = sprite_button_list.at(selected_sprite_id)->button_y - 20.0f;
	}
	
}

void EWindowEditor::reset_mode(ESprite* _spr)
{
	*_spr->rotate_by_move = false;
	*_spr->rotate_by_target = false;
	*_spr->wall_mode = false;
}

void EWindowEditor::update_on_entity_select()
{
	if (selected_entity != NULL)
	{
		link_to_entity_mass_button->text = std::to_string(*selected_entity->mass);

		EWindow::window_editor->selected_or_unselected_color(link_to_entity_inmovable_button, *EWindow::window_editor->selected_entity->inmovable);
		EWindow::window_editor->selected_or_unselected_color(link_to_entity_controlled_by_player_button, EWindow::window_editor->selected_entity->controlled_by_player);
		EWindow::window_editor->selected_or_unselected_color(link_to_entity_controlled_by_AI_button, EWindow::window_editor->selected_entity->controlled_by_ai);
	}
}
