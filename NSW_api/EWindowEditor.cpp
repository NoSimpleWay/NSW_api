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
	but = new EButton(120.0f, 0.0f, 20.0f, 20.0f);
	but->master_button = link_to_add_new_sprite_button;
	but->master_window = this;
	but->have_rama = true;

	but->master_position = Enums::PositionMaster::BUTTON;
	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::MID;
	but->text = "4";

	but->action_on_left_click = &EBA::action_set_sprite_mode_4;

	button_list.push_back(but);
	link_to_sprite_editor_group.push_back(but);


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


	for (int i = 0; i < 8; i++)
	{
		//edd new entity
		but = new EButton(0.0f + i * 22.0f, -10.0f, 20.0f, 20.0f);
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

	if (glfwGetKey(EWindow::main_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		editor_mode = EditMode::SelectEntities;
		EWindow::button_main_group_pressed = true;
		update_sprite_buttons();
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
		Entity* clone = new Entity();
		*clone->position_x = *selected_entity->position_x;
		*clone->position_y = *selected_entity->position_y;

		*clone->mass = *selected_entity->mass;

		*clone->collision_down = *selected_entity->collision_down;
		*clone->collision_left = *selected_entity->collision_left;
		*clone->collision_right = *selected_entity->collision_right;
		*clone->collision_up = *selected_entity->collision_up;

		clone->controlled_by_ai = selected_entity->controlled_by_ai;
		clone->controlled_by_player = selected_entity->controlled_by_player;



		for (ESprite* spr : selected_entity->sprite_list)
		{
			int id = 0;

			ESprite* clone_sprite = new ESprite();
			clone->sprite_list.push_back(spr);

			clone_sprite->rotate_by_move = spr->rotate_by_move;
			clone_sprite->rotate_by_target = spr->rotate_by_target;

			for (EGabarite* g : spr->gabarite)
			{
				clone_sprite->gabarite.push_back(g);
				clone_sprite->offset_x.push_back(spr->offset_x.at(id));
				clone_sprite->offset_y.push_back(spr->offset_y.at(id));

				id++;
			}
		}

		*clone->position_x = round( ECamera::get_world_position_x(EWindow::window_test->game_camera) );
		*clone->position_y = round( ECamera::get_world_position_y(EWindow::window_test->game_camera) );

		selected_entity = clone;

		ECluster::put_entity(clone);

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
		update_sprite_buttons();
	}

	for (int i = 0; i < sprite_button_list.size(); i++)
	{

		if (sprite_button_list.at(i)->need_remove)
		{
			if (selected_sprite_id == i)
			{
				selected_sprite_id--;
				if (selected_sprite_id < 0)
				{
					selected_sprite_id = 0;
				}
			}
			sprite_button_list.erase(sprite_button_list.begin() + i);

			selected_entity->sprite_list.erase(selected_entity->sprite_list.begin() + i);

			any_remove = true;
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

	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_C) == GLFW_PRESS) & (selected_entity != NULL))
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

			*selected_entity->need_change_cluster = true;

			SetCursorPos(saved_pos_x, saved_pos_y);
			prev_mouse_x = saved_pos_x;
			prev_mouse_y = saved_pos_y;
			//EWindow::push_cursor(EWindow::mouse_speed_x, EWindow::mouse_speed_y);
		}
	}
	else
	{
		if (started_entity_move)
		{
			*selected_entity->position_x = round(*selected_entity->position_x);
			*selected_entity->position_y = round(*selected_entity->position_y);
		}
		started_entity_move = false;

		
		
	}

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
}

void EWindowEditor::draw_interface(float _d)
{
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
					sprite_button_list.at(i)->rama_color->set_color(EColor::COLOR_ORANGE);
					sprite_button_list.at(i)->rama_thikness = 5.0f;


					yy -= 30.0f;
					sprite_button_list.at(i)->gabarite = selected_entity->sprite_list.at(i)->gabarite.at(selected_frame_id);
				}
				else
				{
					sprite_button_list.at(i)->rama_color->set_color(EColor::COLOR_BLACK);
					sprite_button_list.at(i)->rama_thikness = 2.0f;
					sprite_button_list.at(i)->gabarite = selected_entity->sprite_list.at(i)->gabarite.at(0);
				}

				sprite_button_list.at(i)->data_id = i;
			}

			for (EButton* b : link_to_sprite_frame)
			{
				b->master_button = sprite_button_list.at(selected_sprite_id);
			}

			for (int i = 0; i < link_to_sprite_frame.size(); i++)
			{
				EButton* fr = link_to_sprite_frame.at(i);
				//std::cout << "process:" << z << std::endl;
				if (i < selected_entity->sprite_list.at(selected_sprite_id)->gabarite.size())
				{
					fr->is_active = true;
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
