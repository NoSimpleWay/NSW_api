#include "EWindowEditor.h"
#include "EWindowTest.h"



EWindowEditor::EWindowEditor()
{


	EButton* but;
	for (int i = 0; i < 20; i++)
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
	but = new EButton(5.0f, 0.0f, 20.0f, 20.0f);
	but->master_button = sprite_button_list.at(selected_frame_id);
	but->master_window = this;
	but->have_description = true;
	but->have_icon = true;
	but->have_rama = true;

	but->master_position = Enums::PositionMaster::BUTTON;
	but->position_mode_x = Enums::PositionMode::SUPER_RIGHT;
	but->position_mode_y = Enums::PositionMode::MID;
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
/////	set 4 textures mode (movement)		////////////////
///////////////////////////////////////////////
	but = new EButton(0.0f, -5.0f, 20.0f, 20.0f);
	but->master_button = sprite_button_list.at(selected_frame_id);
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
/////	set 8 textures mode(gun target)		////////////////
///////////////////////////////////////////////
	but = new EButton(3.0f, 0.0f, 20.0f, 20.0f);
	but->master_button = link_to_is_rotate_by_move_button;
	but->master_window = this;
	but->have_rama = true;

	but->master_position = Enums::PositionMaster::BUTTON;
	but->position_mode_x = Enums::PositionMode::SUPER_RIGHT;
	but->position_mode_y = Enums::PositionMode::MID;
	but->text = "8";

	but->action_on_left_click = &EBA::action_set_sprite_mode_8;

	button_list.push_back(but);
	link_to_sprite_editor_group.push_back(but);
	link_to_is_rotate_by_gun_target_button = but;

	////////////////////////////////////////////////
/////	set wall mode		////////////////
///////////////////////////////////////////////
	but = new EButton(3.0f, 00.0f, 20.0f, 20.0f);
	but->master_button = link_to_is_rotate_by_gun_target_button;
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

	////////////////////////////////////////////////
/////	set shadow mode		////////////////
///////////////////////////////////////////////
	but = new EButton(3.0f, 00.0f, 20.0f, 20.0f);
	but->master_button = link_to_is_wall_mode;
	but->master_window = this;
	but->have_rama = true;

	but->master_position = Enums::PositionMaster::BUTTON;
	but->position_mode_x = Enums::PositionMode::SUPER_RIGHT;
	but->position_mode_y = Enums::PositionMode::MID;
	but->text = "sh";

	but->action_on_left_click = &EBA::action_set_shadow_mode;

	button_list.push_back(but);
	link_to_sprite_editor_group.push_back(but);
	link_to_is_shadow = but;


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

	/*
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

	//entity tall shadow value
	but = new EButton(0.0f, -3.0f, 150.0f, 16.0f);
	but->master_position = Enums::PositionMaster::BUTTON;
	but->master_button = link_to_entity_mass_button;
	but->master_window = this;
	but->action_on_input_finish = &EBA::action_set_tall;

	button_list.push_back(but);
	link_to_entity_shadow_tall_button = but;
	but->input_only_numbers = true;

	but->text = "0";
	but->input_hint = "shadow tall";
	but->have_input_mode = true;

	but->position_mode_x = Enums::PositionMode::LEFT;
	but->position_mode_y = Enums::PositionMode::DOWN;

	//entity inmovable
	but = new EButton(0.0f, -3.0f, 150.0f, 16.0f);
	but->master_position = Enums::PositionMaster::BUTTON;
	but->master_button = link_to_entity_shadow_tall_button;
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
	*/
	for (int i = 0; i < 8; i++)
	{
		//frames
		but = new EButton(0.0f + i * 42.0f, -40.0f, 40.0f, 40.0f);
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

	for (int i = 0; i < 3; i++)
	{
		but = new EButton(500.0f + 36.0f * i, -10.0f, 30.0f, 30.0f);
		but->master_window = this;
		but->have_icon = true;


		if (i == 0) { but->gabarite = ETextureAtlas::put_texture_to_atlas("data/textures/button_gabarite_mode_collision.png", EWindow::default_texture_atlas); }
		if (i == 1) { but->gabarite = ETextureAtlas::put_texture_to_atlas("data/textures/button_gabarite_mode_path_block.png", EWindow::default_texture_atlas); }
		if (i == 2) { but->gabarite = ETextureAtlas::put_texture_to_atlas("data/textures/button_gabarite_mode_shadow_block.png", EWindow::default_texture_atlas); }

		but->have_rama = true;
		but->data_id = i;

		but->position_mode_x = Enums::PositionMode::LEFT;
		but->position_mode_y = Enums::PositionMode::UP;
		but->action_on_left_click = &EBA::action_select_entity_gabarite_mode;

		button_list.push_back(but);
		select_gabarite_mode_button_list.push_back(but);
	}



	////////////////////////////////////////////////
/////	lightsource color red		////////////////
///////////////////////////////////////////////
	but = new EButton(-120.0f, 00.0f, 200.0f, 20.0f);
	but->master_window = this;
	but->have_description = true;
	but->have_icon = true;
	but->have_rama = true;

	but->bg_color->set_color(EColor::COLOR_RED);
	but->data_id = 0;

	but->master_position = Enums::PositionMaster::WINDOW;
	but->position_mode_x = Enums::PositionMode::RIGHT;
	but->position_mode_y = Enums::PositionMode::DOWN;
	but->text = "";
	but->slider_value = EColor::COLOR_SKY_AMBIENT->color_red;
	but->is_slider = true;

	but->action_on_slider_drag = &EBA::action_slider_light_source_color;

	link_to_lightsource_red = but;
	button_list.push_back(but);

	////////////////////////////////////////////////
/////	sky color green		////////////////
///////////////////////////////////////////////
	but = new EButton(-120.0f, 25.0f, 200.0f, 20.0f);
	but->master_window = this;
	but->have_description = true;
	but->have_icon = true;
	but->have_rama = true;

	but->bg_color->set_color(EColor::COLOR_GREEN);
	but->data_id = 1;

	but->master_position = Enums::PositionMaster::WINDOW;
	but->position_mode_x = Enums::PositionMode::RIGHT;
	but->position_mode_y = Enums::PositionMode::DOWN;
	but->text = "";
	but->slider_value = EColor::COLOR_SKY_AMBIENT->color_green;
	but->is_slider = true;

	but->action_on_slider_drag = &EBA::action_slider_light_source_color;

	link_to_lightsource_green = but;
	button_list.push_back(but);

	////////////////////////////////////////////////
/////	sky color blue		////////////////
///////////////////////////////////////////////
	but = new EButton(-120.0f, 50.0f, 200.0f, 20.0f);
	but->master_window = this;
	but->have_description = true;
	but->have_icon = true;
	but->have_rama = true;

	but->bg_color->set_color(EColor::COLOR_BLUE);
	but->data_id = 2;

	but->master_position = Enums::PositionMaster::WINDOW;
	but->position_mode_x = Enums::PositionMode::RIGHT;
	but->position_mode_y = Enums::PositionMode::DOWN;
	but->text = "";
	but->slider_value = EColor::COLOR_SKY_AMBIENT->color_blue;
	but->is_slider = true;

	but->action_on_slider_drag = &EBA::action_slider_light_source_color;

	link_to_lightsource_blue = but;
	button_list.push_back(but);


	//

	align_x = Enums::PositionMode::RIGHT;
	align_y = Enums::PositionMode::UP;

	window_size_x = 300.0f;
	window_size_y = 600.0f;

	update_sprite_buttons();

	//default_resize_event();

	button_group_start_x = -250.0f;
	button_group_start_y = 460.0f;

	add_button_group_for_float_data(Entity::EAttr::ENTITY_ATTRIBUTE_MASS);
	add_button_group_for_float_data(Entity::EAttr::ENTITY_ATTRIBUTE_SHADOW_TALL);
	add_button_group_for_float_data(Entity::EAttr::ENTITY_ATTRIBUTE_SPEED);
	add_button_group_for_float_data(Entity::EAttr::ENTITY_ATTRIBUTE_DRAG);

	button_group_start_x = -16.0f;
	button_group_start_y = 460.0f;
	add_button_group_for_bool_data(Entity::EntityBoolAttributes::ENTITY_BOOL_ATTRIBUTE_INMOVABLE);
	add_button_group_for_bool_data(Entity::EntityBoolAttributes::ENTITY_BOOL_CONTROLLED_BY_AI);
	add_button_group_for_bool_data(Entity::EntityBoolAttributes::ENTITY_BOOL_CONTROLLED_BY_PLAYER);
	add_button_group_for_bool_data(Entity::EntityBoolAttributes::ENTITY_BOOL_HAVE_LIGHT_SOURCE);
	add_button_group_for_bool_data(Entity::EntityBoolAttributes::ENTITY_BOOL_GHOST);
	add_button_group_for_bool_data(Entity::EntityBoolAttributes::ENTITY_BOOL_NO_PATH_BLOCK);




	//////////////////////////////////////////////////////////////////



	//but->data_id = 2;





	//button_list.push_back(but);
	button_array* a_array;
	button_array_collection_massive* a_massive = new button_array_collection_massive(this);
	*a_massive->size_x = 500.0f;
	*a_massive->size_y = 100.0f;
	*a_massive->position_x = 100.0f;
	*a_massive->position_y = 120.0f;

	button_array_horizontal_collection* a_horizontal = new button_array_horizontal_collection(5.0f, 5.0f, 200.0f, 150.0f);

	for (int i = 0; i < 5; i++)
	{
		but = new EButton(0.0f, 0.0f, 100.0f, 20.0f);
		but->text = "TAB #" + std::to_string(i);
		but->master_window = this;
		a_horizontal->tab_button_list.push_back(but);

		but->data_id = i;
		*but->target_value_for_int = i;
		but->target_address_for_int = a_horizontal->selected_tab;
		but->action_on_left_click = &EBA::action_set_constant_int_to_address;
	}

	button_array_vertical_collection* a_vertical = new button_array_vertical_collection(5.0f, 5.0f, 0.0f, 0.0f);
	*a_vertical->selected_distance_between_button_mode = button_array_vertical_collection::BUTTON_DISTANCE_ALIGN_RULE::BUTTON_SIZE;



	for (int f = 0; f < 1; f++)
	{
		///
		a_array = new button_array;

		but = new EButton(0.0, 0.0f, 200.0f, 10.0f);
		but->bg_color->set_color(EColor::COLOR_GREEN);
		but->master_window = this;
		but->text = "Blur factor";
		but->is_slider = true;
		but->slider_value_multiplier = 1.0f;
		but->target_address_for_float = &EWindowTest::blur_factor;
		but->action_on_slider_drag = &EBA::action_set_button_value_float_to_address;
		a_array->button_list.push_back(but);
		a_vertical->button_array_list.push_back(a_array);

		a_array = new button_array;

		but = EButton::clone_button(but, 0.0f, 0.0f, 100.0f, 15.0f);
		but->text = "Blur decay multiplier";
		but->target_address_for_float = &EWindowTest::blur_decay_multiplier_factor;
		a_array->button_list.push_back(but);
		a_vertical->button_array_list.push_back(a_array);

		a_array = new button_array;
		but = EButton::clone_button(but, 0.0f, 0.0f, 100.0f, 15.0f);

		but->text = "Blur decay flat";

		but->slider_value_multiplier = 0.1f;
		but->target_address_for_float = &EWindowTest::blur_decay_flat_factor;

		a_array->button_list.push_back(but);
		a_vertical->button_array_list.push_back(a_array);

		a_array = new button_array;
		but = new EButton(0.0f, 45.0f, 200.0f, 10.0f);
		but->master_window = this;
		but->text = "Add factor";
		but->is_slider = true;
		but->slider_value_multiplier = 1.0f;
		but->target_address_for_float = &EWindowTest::add_factor;
		but->action_on_slider_drag = &EBA::action_set_button_value_float_to_address;
		a_array->button_list.push_back(but);
		a_vertical->button_array_list.push_back(a_array);


	}


	a_horizontal->button_array_vertical_collection_list.push_back(a_vertical);
	a_massive->button_array_horizontal_collection_list.push_back(a_horizontal);

	button_array_collection_massive_list.push_back(a_massive);




	/// <summary>
	/// AUTOBUILDING GENERATOR MASSIVE
	/// </summary>
	a_massive = new button_array_collection_massive(this);
	*a_massive->is_active = false;
	button_array_collection_massive_list.push_back(a_massive);
	autobuilding_massive_link = a_massive;
	*a_massive->size_x = 300.0f;
	*a_massive->size_y = 100.0f;
	*a_massive->position_x = 0;
	*a_massive->position_y = 0;


	//****************************************
	//"add new texture" variant button
	//****************************************
			a_horizontal = new button_array_horizontal_collection(5.0f, 5.0f, 200.0f, 30.0f);
			a_massive->button_array_horizontal_collection_list.push_back(a_horizontal);

			a_vertical = new button_array_vertical_collection(5.0f, 5.0f, 200.0f, 150.0f);
			*a_vertical->selected_distance_between_button_mode = button_array_vertical_collection::BUTTON_DISTANCE_ALIGN_RULE::BUTTON_SIZE;
			a_horizontal->button_array_vertical_collection_list.push_back(a_vertical);


			a_array = new button_array;
			a_vertical->button_array_list.push_back(a_array);

			but = new EButton(0.0f, 0.0f, 20.0f, 20.0f);
			but->master_window = this;
			but->text = "+";
			but->action_on_left_click = &EBA::action_add_new_texture_variant_button;

			a_array->button_list.push_back(but);

			but = new EButton(0.0f, 0.0f, 20.0f, 20.0f);
			but->master_window = this;
			but->text = "compile sprites";
			but->action_on_left_click = &EBA::action_assembly_autobuilding;

			a_array->button_list.push_back(but);

	//****************************************
	//texture variant button array
	//****************************************
			a_horizontal = new button_array_horizontal_collection(5.0f, 5.0f, 200.0f, 150.0f);
			a_massive->button_array_horizontal_collection_list.push_back(a_horizontal);

			//new vertical group for texture variant
			a_vertical = new button_array_vertical_collection(5.0f, 5.0f, 200.0f, 150.0f);
			*a_vertical->selected_distance_between_button_mode = button_array_vertical_collection::BUTTON_DISTANCE_ALIGN_RULE::BUTTON_SIZE;
			a_horizontal->button_array_vertical_collection_list.push_back(a_vertical);


			//texture variant button array
			a_array = new button_array;
			link_to_texture_variant_array = a_array;

			//add array to vertical group
			a_vertical->button_array_list.push_back(a_array);
	

			//generate new buttons
			for (int i = 0; i < 10; i++)
			{
				but = new EButton(0.0f, 0.0f, 50.0f, 50.0f);
				but->master_window = this;
				but->text = "";
				but->have_rama = true;

				a_array->button_list.push_back(but);
				//but->action_on_right_click = &EBA::action_set_button_as_removed;
				//but->can_be_removed = true;
				but->action_on_right_click = &EBA::action_deactivate_texture_variant;
				but->action_on_left_click = &EBA::action_select_texture_variant;
				but->action_on_left_double_click = &EBA::action_open_select_texture_window;
				but->have_icon = true;

				but->data_id = i;

				//building_autogenerator_link_to_texture_variant.push_back(but);
			}

			//save button style for future
			texture_variant_style_button = but;

			//a_array->button_list.push_back(but);



	//****************************************
	//building autogenerator elements
	//****************************************
	a_horizontal = new button_array_horizontal_collection(5.0f, 5.0f, 200.0f, 235.0f);
	a_massive->button_array_horizontal_collection_list.push_back(a_horizontal);

	//new vertical group for texture variant
	a_vertical = new button_array_vertical_collection(5.0f, 5.0f, 200.0f, 230.0f);
	*a_vertical->selected_distance_between_button_mode = button_array_vertical_collection::BUTTON_DISTANCE_ALIGN_RULE::FREE;
	a_horizontal->button_array_vertical_collection_list.push_back(a_vertical);


	//texture variant button array
	a_array = new button_array;
	a_vertical->button_array_list.push_back(a_array);

	for (int yy = 0; yy < 4; yy++)
	for (int xx = 0; xx < 3; xx++)
	{
		/*
		//left wall
		if (i == 0)
		{
			but = new EButton(0.0f, 0.0f, 50.0f, 50.0f);
			building_autogenerator_link_to_left_wall = but;
			building_autogenerator_wall_button_link.push_back(but);
		}

		//mid wall
		if (i == 1)
		{
			but = new EButton(55.0f, 0.0f, 50.0f, 50.0f);
			building_autogenerator_link_to_mid_wall = but;
			building_autogenerator_wall_button_link.push_back(but);
		}

		//right wall
		if (i == 2)
		{
			but = new EButton(110.0f, 0.0f, 50.0f, 50.0f);
			building_autogenerator_link_to_right_wall = but;
			building_autogenerator_wall_button_link.push_back(but);
		}

		//window
		if (i == 3)
		{
			but = new EButton(55.0f, 55.0f, 50.0f, 50.0f);
			building_autogenerator_link_to_window_wall = but;
			building_autogenerator_wall_button_link.push_back(but);
		}*/


		but = new EButton(0.0f + xx * 55.0f, 0.0f + yy * 55.0f, 50.0f, 50.0f);
		//building_autogenerator_link_to_left_wall = but;
		building_autogenerator_wall_button_link.push_back(but);

		but->master_window = this;
		but->have_icon = true;
		but->have_rama = true;
		but->data_id = xx + yy* 3;

		but->action_on_left_click = &EBA::action_select_building_autogenerator_wall_element;

		a_array->button_list.push_back(but);
	}

	but = new EButton(200.0f, 0.0f, 50.0f, 50.0f);
	//building_autogenerator_link_to_left_wall = but;
	building_autogenerator_wall_button_link.push_back(but);

	but->master_window = this;
	but->have_icon = true;
	but->have_rama = true;
	but->data_id = 12;

	but->action_on_left_click = &EBA::action_select_building_autogenerator_wall_element;

	a_array->button_list.push_back(but);


	//****************************************
	//"add new floor" button
	//****************************************
	a_horizontal = new button_array_horizontal_collection(5.0f, 5.0f, 200.0f, 30.0f);
	a_massive->button_array_horizontal_collection_list.push_back(a_horizontal);

	a_vertical = new button_array_vertical_collection(5.0f, 5.0f, 200.0f, 150.0f);
	a_horizontal->button_array_vertical_collection_list.push_back(a_vertical);


	a_array = new button_array;
	a_vertical->button_array_list.push_back(a_array);
	*a_vertical->selected_distance_between_button_mode = button_array_vertical_collection::BUTTON_DISTANCE_ALIGN_RULE::BUTTON_SIZE;

	but = new EButton(0.0f, 0.0f, 20.0f, 20.0f);
	but->master_window = this;
	but->text = "add new floor";
	but->action_on_left_click = &EBA::action_add_new_floor;
	a_array->button_list.push_back(but);

	but = new EButton(0.0f, 0.0f, 20.0f, 20.0f);
	but->master_window = this;
	but->text = "<";
	but->data_id = 0;
	but->action_on_left_click = &EBA::action_move_floor_order;
	a_array->button_list.push_back(but);

	but = new EButton(0.0f, 0.0f, 20.0f, 20.0f);
	but->master_window = this;
	but->text = ">";
	but->data_id = 1;
	but->action_on_left_click = &EBA::action_move_floor_order;

	a_array->button_list.push_back(but);



	//****************************************
	//floors button array
	//****************************************
	a_horizontal = new button_array_horizontal_collection(5.0f, 5.0f, 200.0f, 150.0f);
	a_massive->button_array_horizontal_collection_list.push_back(a_horizontal);

	//new vertical group for texture variant
	a_vertical = new button_array_vertical_collection(5.0f, 5.0f, 200.0f, 150.0f);
	*a_vertical->selected_distance_between_button_mode = button_array_vertical_collection::BUTTON_DISTANCE_ALIGN_RULE::BUTTON_SIZE;
	a_horizontal->button_array_vertical_collection_list.push_back(a_vertical);


	//texture variant button array
	a_array = new button_array;
	link_to_floors_array = a_array;

	//add array to vertical group
	a_vertical->button_array_list.push_back(a_array);


	//generate new buttons
	for (int i = 0; i < 10; i++)
	{
		but = new EButton(0.0f, 0.0f, 25.0f, 15.0f);
		but->master_window = this;
		but->text = "floor #" + std::to_string(i);
		but->have_rama = true;

		a_array->button_list.push_back(but);
		//but->action_on_right_click = &EBA::action_set_button_as_removed;
		//but->can_be_removed = true;
		but->action_on_right_click = &EBA::action_deactivate_floors;
		but->action_on_left_click = &EBA::action_select_floor;
		but->have_icon = false;

		but->data_id = i;

		//building_autogenerator_link_to_texture_variant.push_back(but);
	}

	a_horizontal = new button_array_horizontal_collection(5.0f, 5.0f, 200.0f, 150.0f);
	a_massive->button_array_horizontal_collection_list.push_back(a_horizontal);

	//new vertical group for texture variant
	a_vertical = new button_array_vertical_collection(5.0f, 5.0f, 200.0f, 150.0f);
	*a_vertical->selected_distance_between_button_mode = button_array_vertical_collection::BUTTON_DISTANCE_ALIGN_RULE::BUTTON_SIZE;
	a_horizontal->button_array_vertical_collection_list.push_back(a_vertical);

	//texture variant button array
	a_array = new button_array;
	//link_to_floors_array = a_array;

	//add array to vertical group
	a_vertical->button_array_list.push_back(a_array);

		but = new EButton(0.0f, 0.0f, 100.0f, 15.0f);
			but->master_window = this;
			but->is_slider = true;
			but->slider_value = 0.0f;
			but->target_address_for_float = NULL;
			but->action_on_slider_drag = &EBA::action_set_button_value_float_to_address;

			but->text = "bottom roof";
			a_array->button_list.push_back(but);

			link_to_bottom_floor_slider = but;
		

		but = new EButton(0.0f, 0.0f, 100.0f, 15.0f);
			but->master_window = this;
			but->is_slider = true;
			but->slider_value = 0.0f;
			but->target_address_for_float = NULL;
			but->action_on_slider_drag = &EBA::action_set_button_value_float_to_address;

			but->text = "horizontal roof";
			a_array->button_list.push_back(but);
			link_to_horizontal_floor_slider = but;

	a_vertical = new button_array_vertical_collection(5.0f, 35.0f, 200.0f, 150.0f);
	*a_vertical->selected_distance_between_button_mode = button_array_vertical_collection::BUTTON_DISTANCE_ALIGN_RULE::BUTTON_SIZE;
	a_horizontal->button_array_vertical_collection_list.push_back(a_vertical);


	a_array = new button_array;
	a_vertical->button_array_list.push_back(a_array);

	but = new EButton(0.0f, 0.0f, 100.0f, 15.0f);
	but->master_window = this;
	but->is_slider = true;
	but->slider_value = 0.0f;
	but->target_address_for_float = NULL;
	but->action_on_slider_drag = &EBA::action_set_button_value_float_to_address;

	but->text = "up roof";
	a_array->button_list.push_back(but);

	link_to_up_floor_slider = but;


	//save button style for future
	texture_variant_style_button = but;

	//a_array->button_list.push_back(but);



}

EWindowEditor::~EWindowEditor()
{
}


float EWindowEditor::get_move_multiplier(float _zoom)
{
	if
		(
		(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			||
			(glfwGetKey(EWindow::main_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
			)
	{
		return 0.1f * _zoom;
	}

	return 1.0f * _zoom;
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

	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_SPACE) == GLFW_PRESS) & (!EButton::any_input))
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

	if (((glfwGetKey(EWindow::main_window, GLFW_KEY_COMMA) == GLFW_PRESS) & (!EWindow::button_main_group_pressed) & (editor_mode == EditMode::EditSprites)) & (!EButton::any_input))
	{
		EWindow::button_main_group_pressed = true;

		(*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(selected_frame_id)->copies)--;
		
		if (*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(selected_frame_id)->copies < 1)
		{
			*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(selected_frame_id)->copies = 1;
		}
		//selected_entity
	}

	if (((glfwGetKey(EWindow::main_window, GLFW_KEY_COMMA) == GLFW_PRESS) & (!EWindow::button_main_group_pressed) & (editor_mode == EditMode::EditAutobuilding))&(!EButton::any_input))
	{
		EWindow::button_main_group_pressed = true;

		(*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->repeat_x)-= 0.1f;

		if (*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->repeat_x < 0.0f)
		{*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->repeat_x = 0.0f;}
		//selected_entity
		//Entity::assembly_autobuilding_sprites(selected_entity);
	}

	if (((glfwGetKey(EWindow::main_window, GLFW_KEY_PERIOD) == GLFW_PRESS) & (!EWindow::button_main_group_pressed) & (editor_mode == EditMode::EditAutobuilding)) & (!EButton::any_input))
	{
		EWindow::button_main_group_pressed = true;

		(*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->repeat_x)+= 0.1f;

		if (*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->repeat_x > 32.0f)
		{
			*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->repeat_x = 32.0f;
		}
		//selected_entity

		//Entity::assembly_autobuilding_sprites(selected_entity);
	}

	if (((glfwGetKey(EWindow::main_window, GLFW_KEY_PERIOD) == GLFW_PRESS) & (!EWindow::button_main_group_pressed) & (editor_mode == EditMode::EditSprites))& (!EButton::any_input))
	{
		EWindow::button_main_group_pressed = true;

		(*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(selected_frame_id)->copies)++;
		
		if (*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(selected_frame_id)->copies > 100)
		{
			*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(selected_frame_id)->copies = 100;
		}

		//Entity::assembly_autobuilding_sprites(selected_entity);
		//selected_entity
	}

	if
	(
		(glfwGetKey(EWindow::main_window, GLFW_KEY_E) == GLFW_PRESS)
		&
		(
			(!glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			&
			(!glfwGetKey(EWindow::main_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		)
		&
		(!EWindow::button_main_group_pressed)
		&
		(selected_entity != NULL)
		&
		(!EButton::any_input)
		&
		(editor_mode == EditMode::SelectEntities)
	)
	{
		editor_mode = EditMode::EditSprites;
		EWindow::button_main_group_pressed = true;
		update_sprite_buttons();

	}

	if
	(
		(glfwGetKey(EWindow::main_window, GLFW_KEY_E) == GLFW_PRESS)
		&
		(
			(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			||
			(glfwGetKey(EWindow::main_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		)
		&
		(!EWindow::button_main_group_pressed)
		&
		(selected_entity != NULL)
		&
		(!EButton::any_input)
	)
	{
		editor_mode = EditMode::EditAutobuilding;
		EWindow::button_main_group_pressed = true;
		*autobuilding_massive_link->is_active = true;
		//refresh_autobuilding();
		//EWindow::window_editor->select_new_floor();
		//EWindow::window_editor->select_new_variant();
		Entity::update_building_autogenerator_massive(selected_entity);

		autobuilding_selected_floor = 0;
		autobuilding_selected_wall = 0;
		autobuilding_selected_texture_variant = 0;

		EWindow::window_editor->select_new_floor();
		EWindow::window_editor->select_new_wall();
		EWindow::window_editor->select_new_variant();

	}

	if (((glfwGetKey(EWindow::main_window, GLFW_KEY_DELETE) == GLFW_PRESS) & (!EWindow::button_main_group_pressed) & (selected_entity != NULL))&(!EButton::any_input))
	{
		EWindow::button_main_group_pressed = true;
		*selected_entity->need_remove = true;
		selected_entity = NULL;

	}

	if (((glfwGetKey(EWindow::main_window, GLFW_KEY_V) == GLFW_PRESS) & (!EWindow::button_main_group_pressed) & (selected_entity != NULL))&(!EButton::any_input))
	{
		EWindow::button_main_group_pressed = true;
		if
		(
			(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			||
			(glfwGetKey(EWindow::main_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		)
		{
			prev_entity = selected_entity;
		}
				
		clone_entity(selected_entity);


		if
		(
			(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			||
			(glfwGetKey(EWindow::main_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		)
		{
			if (ECamera::get_world_position_y(EWindow::window_test->game_camera) >= *prev_entity->position_y+*prev_entity->collision_up)
			{
				*selected_entity->position_x = *prev_entity->position_x;
				*selected_entity->position_y = *prev_entity->position_y + *prev_entity->collision_up + *selected_entity->collision_down;

				*selected_entity->need_change_cluster = true;
			}
		}

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

				float dst_x = *selected_entity->position_x + *sp->sprite_struct_list.at(0)->offset_x - xx;
				float dst_y = *selected_entity->position_y + *sp->sprite_struct_list.at(0)->offset_y - yy;
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

		if (editor_mode == EditMode::EditAutobuilding)
		{
			autobuilding_selected_floor = 0;
			autobuilding_selected_wall = 0;
			autobuilding_selected_texture_variant = 0;

			count_of_floors = selected_entity->autobuilding_floor_list.size();

			if (count_of_floors > 0)
			{
				count_of_variants
					=
					selected_entity->
					autobuilding_floor_list.at(autobuilding_selected_floor)->
					wall_list.at(autobuilding_selected_wall)->
					texture_variant_list.size();
			}
			else
			{
				count_of_variants = 0;
			}



			window_editor->refresh_autobuilding();
		}
		//Entity::update_building_autogenerator_massive(selected_entity);

		update_on_entity_select();

		if (editor_mode == EditMode::EditSprites)
		{update_sprite_buttons();}
	}

	for (int i = 0; i < sprite_button_list.size(); i++)
	{
		//EWindow::window_editor->selected_frame_id = 0;

		if (*sprite_button_list.at(i)->need_remove)
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
			*sprite_button_list.at(i)->need_remove = false;
		}

	}

	if (any_remove)
	{
		EWindow::window_editor->update_sprite_buttons();
	}

	if ((selected_entity != NULL))
	{
		/*
		if (glfwGetKey(EWindow::main_window, GLFW_KEY_KP_0) == GLFW_PRESS)
		{
			if ((editor_mode == EditMode::EditAutobuilding))
			{

			}
		}*/

		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_X) == GLFW_PRESS)& (!EButton::any_input))
		{
			if (!started_sprite_move)
			{
				saved_pos_x = real_mouse_x;
				saved_pos_y = real_mouse_y;
			}

			started_sprite_move = true;

			if (selected_entity != NULL)
			{
				float mul = get_move_multiplier(1.0f / EWindow::window_test->game_camera->zoom);

				if ((editor_mode == EditMode::EditSprites) & (!selected_entity->sprite_list.empty()))
				{
					*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(EWindow::window_editor->selected_frame_id)->offset_x += mouse_speed_x * mul;
					*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(EWindow::window_editor->selected_frame_id)->offset_y += mouse_speed_y * mul;
				}

				if ((editor_mode == EditMode::EditAutobuilding))
				{
					if (move_mode == MoveMode::MoveTexture)
					{
						*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->texture_variant_list.at(autobuilding_selected_texture_variant)->offset_x += mouse_speed_x * mul;
						*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->texture_variant_list.at(autobuilding_selected_texture_variant)->offset_y += mouse_speed_y * mul;

						if ((glfwGetKey(EWindow::main_window, GLFW_KEY_KP_0) == GLFW_PRESS)&(!EButton::any_input))
						{
							*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->texture_variant_list.at(autobuilding_selected_texture_variant)->offset_x = 0.0f;
							*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->texture_variant_list.at(autobuilding_selected_texture_variant)->offset_y = 0.0f;
						}
					}

					if (move_mode == MoveMode::MoveWall)
					{

						*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->offset_x += mouse_speed_x * mul;
						*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->offset_y += mouse_speed_y * mul;
						
						if ((glfwGetKey(EWindow::main_window, GLFW_KEY_KP_0) == GLFW_PRESS)&(!EButton::any_input))
						{
							*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->offset_x = 0.0f;
							*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->offset_y = 0.0f;
						}

					}

					if (move_mode == MoveMode::MoveFloor)
					{
						*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->offset_x += mouse_speed_x * mul;
						*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->offset_y += mouse_speed_y * mul;

						if ((glfwGetKey(EWindow::main_window, GLFW_KEY_KP_0) == GLFW_PRESS) & (!EButton::any_input))
						{
							*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->offset_x = 0.0f;
							*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->offset_y = 0.0f;
						}
					}
					//*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(EWindow::window_editor->selected_frame_id)->offset_y += mouse_speed_y * mul;

					//Entity::assembly_autobuilding_sprites(selected_entity);
				}


				SetCursorPos(saved_pos_x, saved_pos_y);
				prev_mouse_x = saved_pos_x;
				prev_mouse_y = saved_pos_y;
				//EWindow::push_cursor(EWindow::mouse_speed_x, EWindow::mouse_speed_y);
			}
		}
		else
		{
			if ((glfwGetKey(EWindow::main_window, GLFW_KEY_KP_0) == GLFW_PRESS) & (!EButton::any_input))
			{
				*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->texture_variant_list.at(autobuilding_selected_texture_variant)->offset_x = 0.0f;
				*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->texture_variant_list.at(autobuilding_selected_texture_variant)->offset_y = 0.0f;

				*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->offset_x = 0.0f;
				*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->offset_y = 0.0f;

				//*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->offset_x = 0.0f;
				//*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->offset_y = 0.0f;

				refresh_autobuilding();
				//Entity::assembly_autobuilding_sprites(selected_entity);
			}

			if (started_sprite_move)
			{
				if (editor_mode == EditMode::EditSprites)
				{
					*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(EWindow::window_editor->selected_frame_id)->offset_x = round(*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(EWindow::window_editor->selected_frame_id)->offset_x);
					*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(EWindow::window_editor->selected_frame_id)->offset_y = round(*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(EWindow::window_editor->selected_frame_id)->offset_y);
				}

				if (editor_mode == EditMode::EditAutobuilding)
				{


					if (move_mode == MoveMode::MoveTexture)
					{
						*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->texture_variant_list.at(autobuilding_selected_texture_variant)->offset_x
							=
							round(*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->texture_variant_list.at(autobuilding_selected_texture_variant)->offset_x);

						*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->texture_variant_list.at(autobuilding_selected_texture_variant)->offset_y
							=
							round(*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->texture_variant_list.at(autobuilding_selected_texture_variant)->offset_y);
					}

					if (move_mode == MoveMode::MoveWall)
					{
						*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->offset_x
							=
							round(*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->offset_x);

						*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->offset_y
							=
							round(*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->offset_y);
					}

					if (move_mode == MoveMode::MoveFloor)
					{
						*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->offset_x
							=
							round(*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->offset_x);

						*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->offset_y
							=
							round(*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->offset_y);
					}
					//Entity::assembly_autobuilding_sprites(selected_entity);
				}

				saved_pos_x = -1;
				saved_pos_y = -1;

			}

			started_sprite_move = false;
		}

		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_B) == GLFW_PRESS) & (!EButton::any_input))
		{
			if (!started_shadow_resize)
			{
				saved_pos_x = real_mouse_x;
				saved_pos_y = real_mouse_y;
			}

			started_shadow_resize = true;

			if (selected_entity != NULL)
			{
				float mul = get_move_multiplier(1.0f / EWindow::window_test->game_camera->zoom);

				if (editor_mode == EditMode::EditSprites)
				{
					if (!selected_entity->sprite_list.empty())
					{
						*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(EWindow::window_editor->selected_frame_id)->shadow_size_x -= mouse_speed_x * mul;
						*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(EWindow::window_editor->selected_frame_id)->shadow_size_y += mouse_speed_y * mul;
					}
				}

				if (editor_mode == EditMode::EditAutobuilding)
				{
					*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->repeat_x += mouse_speed_x * 0.01f * mul;
					*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->repeat_y += mouse_speed_y * 0.01f * mul;

					*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->repeat_x
					=
					max(*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->repeat_x, 0.0f);

					*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->repeat_y
					=
					max(*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->repeat_y, 0.0f);

					//Entity::assembly_autobuilding_sprites(selected_entity);
				}

				SetCursorPos(saved_pos_x, saved_pos_y);
				prev_mouse_x = saved_pos_x;
				prev_mouse_y = saved_pos_y;
				//EWindow::push_cursor(EWindow::mouse_speed_x, EWindow::mouse_speed_y);
			}
		}
		else
		{
			if (started_shadow_resize)
			{
				if (editor_mode == EditMode::EditSprites)
				{
					*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(EWindow::window_editor->selected_frame_id)->shadow_size_x = round(*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(EWindow::window_editor->selected_frame_id)->shadow_size_x);
					*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(EWindow::window_editor->selected_frame_id)->shadow_size_y = round(*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(EWindow::window_editor->selected_frame_id)->shadow_size_y);
				}

				/*if (editor_mode == EditMode::EditSprites)
				{
					*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->repeat_x = round(*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->repeat_x);
					*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->repeat_y = round(*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->repeat_y);
					//Entity::assembly_autobuilding_sprites(selected_entity);
				}*/

				saved_pos_x = -1;
				saved_pos_y = -1;
			}

			started_shadow_resize = false;
		}

		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_N) == GLFW_PRESS) & (!EButton::any_input))
		{
			if (!started_shadow_tall)
			{
				saved_pos_x = real_mouse_x;
				saved_pos_y = real_mouse_y;
			}

			started_shadow_tall = true;

			if (selected_entity != NULL)
			{
				float mul = get_move_multiplier(1.0f / EWindow::window_test->game_camera->zoom);

				if (!selected_entity->sprite_list.empty())
				{
					*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(EWindow::window_editor->selected_frame_id)->shadow_tall += mouse_speed_x * mul;
				
				}


				SetCursorPos(saved_pos_x, saved_pos_y);
				prev_mouse_x = saved_pos_x;
				prev_mouse_y = saved_pos_y;
				//EWindow::push_cursor(EWindow::mouse_speed_x, EWindow::mouse_speed_y);
			}
		}
		else
		{
			started_shadow_tall = false;
		}

		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_M) == GLFW_PRESS)&(!EButton::any_input))
		{
			if (!started_shadow_bottom_tall)
			{
				saved_pos_x = real_mouse_x;
				saved_pos_y = real_mouse_y;
			}

			started_shadow_bottom_tall = true;

			if (selected_entity != NULL)
			{
				float mul = get_move_multiplier(1.0f / EWindow::window_test->game_camera->zoom);

				if (!selected_entity->sprite_list.empty())
				{
					*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(EWindow::window_editor->selected_frame_id)->bottom_tall += mouse_speed_x * mul;
				
				}


				SetCursorPos(saved_pos_x, saved_pos_y);
				prev_mouse_x = saved_pos_x;
				prev_mouse_y = saved_pos_y;
				//EWindow::push_cursor(EWindow::mouse_speed_x, EWindow::mouse_speed_y);
			}
		}
		else
		{
			started_shadow_bottom_tall = false;
		}
	}



	if ((editor_mode == EditMode::EditSprites) & (selected_entity != NULL))
	{
		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_Z) == GLFW_PRESS)&(!EButton::any_input))
		{
			if (!started_z_move)
			{
				saved_pos_x = real_mouse_x;
				saved_pos_y = real_mouse_y;
			}

			started_z_move = true;

			if (selected_entity != NULL)
			{
				float mul = get_move_multiplier(1.0f / EWindow::window_test->game_camera->zoom);

				if (!selected_entity->sprite_list.empty())
				{
					*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(EWindow::window_editor->selected_frame_id)->offset_z += mouse_speed_y * mul;

					if (*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(EWindow::window_editor->selected_frame_id)->offset_z < 0)
					{
						*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(EWindow::window_editor->selected_frame_id)->offset_z = 0;
					}
				}


				SetCursorPos(saved_pos_x, saved_pos_y);
				prev_mouse_x = saved_pos_x;
				prev_mouse_y = saved_pos_y;
				//EWindow::push_cursor(EWindow::mouse_speed_x, EWindow::mouse_speed_y);
			}
		}
		else
		{
			if (started_z_move)
			{
				*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(EWindow::window_editor->selected_frame_id)->offset_z = round(*selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(EWindow::window_editor->selected_frame_id)->offset_z);
	

				saved_pos_x = -1;
				saved_pos_y = -1;

			}

			started_z_move = false;
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

			if (*entity_gabarite_mode_active == EntityGabariteMode::EntityGabariteCollision)
			{
				if
					(
					(xx >= *selected_entity->position_x - *selected_entity->collision_left - 10.0f)
						&
						(xx <= *selected_entity->position_x - *selected_entity->collision_left + 10.0f)
						&
						(yy <= *selected_entity->position_y + *selected_entity->collision_up + 10.0f)
						&
						(yy >= *selected_entity->position_y - *selected_entity->collision_down - 10.0f)
						)
				{
					catched_collision_left = true;
				}

				if
					(
					(xx >= *selected_entity->position_x - *selected_entity->collision_left - 10.0f)
						&
						(xx <= *selected_entity->position_x + *selected_entity->collision_right + 10.0f)
						&
						(yy <= *selected_entity->position_y + *selected_entity->collision_up + 10.0f)
						&
						(yy >= *selected_entity->position_y + *selected_entity->collision_up - 10.0f)
						)
				{
					catched_collision_up = true;
				}

				if
					(
					(xx <= *selected_entity->position_x + *selected_entity->collision_right + 10.0f)
						&
						(xx >= *selected_entity->position_x + *selected_entity->collision_right - 10.0f)
						&
						(yy <= *selected_entity->position_y + *selected_entity->collision_up + 10.0f)
						&
						(yy >= *selected_entity->position_y - *selected_entity->collision_down - 10.0f)
						)
				{
					catched_collision_right = true;
				}

				if
					(
					(xx >= *selected_entity->position_x - *selected_entity->collision_left - 10.0f)
						&
						(xx <= *selected_entity->position_x + *selected_entity->collision_right + 10.0f)
						&
						(yy >= *selected_entity->position_y - *selected_entity->collision_down - 10.0f)
						&
						(yy <= *selected_entity->position_y - *selected_entity->collision_down + 10.0f)
						)
				{
					catched_collision_down = true;
				}
			}

			if (*entity_gabarite_mode_active == EntityGabariteMode::EntityGabaritePathBlock)
			{
				if
					(
						(xx >= *selected_entity->position_x - *selected_entity->path_block_gabarite_left - 10.0f)
						&
						(xx <= *selected_entity->position_x - *selected_entity->path_block_gabarite_left + 10.0f)
						&
						(yy <= *selected_entity->position_y + *selected_entity->path_block_gabarite_up + 10.0f)
						&
						(yy >= *selected_entity->position_y - *selected_entity->path_block_gabarite_up - 10.0f)
						)
				{
					catched_collision_left = true;
				}

				if
					(
					(xx >= *selected_entity->position_x - *selected_entity->path_block_gabarite_left - 10.0f)
						&
						(xx <= *selected_entity->position_x + *selected_entity->path_block_gabarite_right + 10.0f)
						&
						(yy <= *selected_entity->position_y + *selected_entity->path_block_gabarite_up + 10.0f)
						&
						(yy >= *selected_entity->position_y + *selected_entity->path_block_gabarite_up - 10.0f)
						)
				{
					catched_collision_up = true;
				}

				if
					(
					(xx <= *selected_entity->position_x + *selected_entity->path_block_gabarite_right + 10.0f)
						&
						(xx >= *selected_entity->position_x + *selected_entity->path_block_gabarite_right - 10.0f)
						&
						(yy <= *selected_entity->position_y + *selected_entity->path_block_gabarite_up + 10.0f)
						&
						(yy >= *selected_entity->position_y - *selected_entity->path_block_gabarite_down - 10.0f)
						)
				{
					catched_collision_right = true;
				}

				if
					(
					(xx >= *selected_entity->position_x - *selected_entity->path_block_gabarite_left - 10.0f)
						&
						(xx <= *selected_entity->position_x + *selected_entity->path_block_gabarite_right + 10.0f)
						&
						(yy >= *selected_entity->position_y - *selected_entity->path_block_gabarite_down - 10.0f)
						&
						(yy <= *selected_entity->position_y - *selected_entity->path_block_gabarite_down + 10.0f)
						)
				{
					catched_collision_down = true;
				}
			}
		}
	

		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_X) == GLFW_PRESS) & (!EButton::any_input))
		{
			Entity::update_path_block(selected_entity);

			if (!started_collision_move)
			{
				saved_pos_x = real_mouse_x;
				saved_pos_y = real_mouse_y;
			}

			started_collision_move = true;
			float mul = get_move_multiplier(1.0f / EWindow::window_test->game_camera->zoom);


			if (catched_collision_down)
			{
				if (*entity_gabarite_mode_active == EntityGabariteMode::EntityGabariteCollision)
				{
					*selected_entity->collision_down -= EWindow::mouse_speed_y * mul;
					*selected_entity->collision_down = EMath::clamp_value_float(*selected_entity->collision_down, 0.0f, 512.0f);
				}

				if (*entity_gabarite_mode_active == EntityGabariteMode::EntityGabaritePathBlock)
				{
					*selected_entity->path_block_gabarite_down -= EWindow::mouse_speed_y * mul;
					*selected_entity->path_block_gabarite_down = EMath::clamp_value_float(*selected_entity->path_block_gabarite_down, 0.0f, 512.0f);
				}
			}

			if (catched_collision_up)
			{
				if (*entity_gabarite_mode_active == EntityGabariteMode::EntityGabariteCollision)
				{
					*selected_entity->collision_up += EWindow::mouse_speed_y * mul;
					*selected_entity->collision_up = EMath::clamp_value_float(*selected_entity->collision_up, 0.0f, 512.0f);
				}

				if (*entity_gabarite_mode_active == EntityGabariteMode::EntityGabaritePathBlock)
				{
					*selected_entity->path_block_gabarite_up += EWindow::mouse_speed_y * mul;
					*selected_entity->path_block_gabarite_up = EMath::clamp_value_float(*selected_entity->path_block_gabarite_up, 0.0f, 512.0f);
				}
			}

			if (catched_collision_left)
			{
				if (*entity_gabarite_mode_active == EntityGabariteMode::EntityGabariteCollision)
				{
					*selected_entity->collision_left -= EWindow::mouse_speed_x * mul;
					*selected_entity->collision_left = EMath::clamp_value_float(*selected_entity->collision_left, 0.0f, 512.0f);
				}

				if (*entity_gabarite_mode_active == EntityGabariteMode::EntityGabaritePathBlock)
				{
					*selected_entity->path_block_gabarite_left -= EWindow::mouse_speed_x * mul;
					*selected_entity->path_block_gabarite_left = EMath::clamp_value_float(*selected_entity->path_block_gabarite_left, 0.0f, 512.0f);
				}
			}

			if (catched_collision_right)
			{
				if (*entity_gabarite_mode_active == EntityGabariteMode::EntityGabariteCollision)
				{
					*selected_entity->collision_right += EWindow::mouse_speed_x * mul;
					*selected_entity->collision_right = EMath::clamp_value_float(*selected_entity->collision_right, 0.0f, 512.0f);
				}

				if (*entity_gabarite_mode_active == EntityGabariteMode::EntityGabaritePathBlock)
				{
					*selected_entity->path_block_gabarite_right += EWindow::mouse_speed_x * mul;
					*selected_entity->path_block_gabarite_right = EMath::clamp_value_float(*selected_entity->path_block_gabarite_right, 0.0f, 512.0f);
				}
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

	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_C) == GLFW_PRESS) & (!EButton::any_input))
	{
		if (!started_entity_move)
		{
			saved_pos_x = real_mouse_x;
			saved_pos_y = real_mouse_y;
		}

		started_entity_move = true;

		
		
		float mul = get_move_multiplier(1.0f / EWindow::window_test->game_camera->zoom);

			if (selected_entity != NULL)
			{
				*selected_entity->position_x += EWindow::mouse_speed_x * mul;
				*selected_entity->position_y += EWindow::mouse_speed_y * mul;

				*selected_entity->need_change_cluster = true;

				Entity::update_path_block(selected_entity);
			}

			if (!selected_entity_list.empty())
			{
				for (Entity* e : selected_entity_list)
				{
					*e->position_x += EWindow::mouse_speed_x * mul;
					*e->position_y += EWindow::mouse_speed_y * mul;

					*e->need_change_cluster = true;
					Entity::update_path_block(e);
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

	if ((editor_mode == EditMode::EditAutobuilding) & (selected_entity != NULL))
	{
		Entity::assembly_autobuilding_sprites(selected_entity);
	}

}

void EWindowEditor::clone_entity(Entity* _e)
{
	Entity* clone = new Entity();
	*clone->position_x = *_e->position_x;
	*clone->position_y = *_e->position_y;

	*clone->collision_down		=	*_e->collision_down;
	*clone->collision_left		=	*_e->collision_left;
	*clone->collision_right		=	*_e->collision_right;
	*clone->collision_up		=	*_e->collision_up;

	int did = 0;

	for (float f :_e->eattr_BASE)
	{
		clone->eattr_BASE.at(did) = f;
		did++;
	}

	did = 0;
	for (bool* b : _e->pointer_to_bool_list)
	{
		*clone->pointer_to_bool_list.at(did) = *b;
		did++;
	}





	for (ESprite* spr : _e->sprite_list)
	{
		int id = 0;

		ESprite* clone_sprite = new ESprite();
		ESprite::sprite_struct* clone_struct = NULL;
		ESprite::clear_default_data(clone_sprite);

		clone->sprite_list.push_back(clone_sprite);
		
		*clone_sprite->rotate_by_move = *spr->rotate_by_move;
		*clone_sprite->rotate_by_target = *spr->rotate_by_target;
		*clone_sprite->rotate_by_target_gun = *spr->rotate_by_target_gun;

		*clone_sprite->is_shadow = *spr->is_shadow;
		*clone_sprite->wall_mode = *spr->wall_mode;
		

		EString::out_debug("size of struct of original sprite: " + std::to_string(spr->sprite_struct_list.size()));
		for (ESprite::sprite_struct* st : spr->sprite_struct_list)
		{
			EString::out_debug("created new struct: " + std::to_string(id));
			clone_struct = new ESprite::sprite_struct;

			clone_sprite->sprite_struct_list.push_back(clone_struct);

			clone_struct->gabarite = st->gabarite;
			clone_struct->supermap = st->supermap;

			*clone_struct->offset_x = *st->offset_x;
			*clone_struct->offset_y = *st->offset_y;
			*clone_struct->offset_z = *st->offset_z;

			*clone_struct->shadow_size_x = *st->shadow_size_x;
			*clone_struct->shadow_size_y = *st->shadow_size_y;
			*clone_struct->shadow_tall = *st->shadow_tall;

			*clone_struct->bottom_tall = *st->bottom_tall;

			*clone_struct->copies = *st->copies;

			id++;
		}
	}

	*clone->position_x = round(EWindow::window_test->game_camera->position_x / EWindow::window_test->game_camera->zoom);
	*clone->position_y = round(EWindow::window_test->game_camera->position_y / EWindow::window_test->game_camera->zoom);

	selected_entity = clone;

	EWindow::window_editor->selected_frame_id = 0;
	EWindow::window_editor->selected_sprite_id = 0;

	Entity::update_entity_attributes(clone);

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

		if (*entity_gabarite_mode_active == EntityGabariteMode::EntityGabariteCollision)
		{
			if (catched_collision_left)
			{
				EGraphicCore::batch->draw_rama
				(
					*selected_entity->position_x - *selected_entity->collision_left - 3.0f,
					*selected_entity->position_y - *selected_entity->collision_down - 3.0f,
					6.0f,
					*selected_entity->collision_down + *selected_entity->collision_up + 3.0f,
					1.0f,
					EGraphicCore::gabarite_white_pixel
				);
			}

			if (catched_collision_up)
			{
				EGraphicCore::batch->draw_rama
				(
					*selected_entity->position_x - *selected_entity->collision_left - 3.0f,
					*selected_entity->position_y + *selected_entity->collision_up - 3.0f,
					*selected_entity->collision_left + *selected_entity->collision_right + 3.0f,
					6.0f,
					1.0f,
					EGraphicCore::gabarite_white_pixel
				);
			}

			if (catched_collision_right)
			{
				EGraphicCore::batch->draw_rama
				(
					*selected_entity->position_x + *selected_entity->collision_right - 3.0f,
					*selected_entity->position_y - *selected_entity->collision_down - 3.0f,
					6.0f,
					*selected_entity->collision_down + *selected_entity->collision_up + 3.0f,
					1.0f,
					EGraphicCore::gabarite_white_pixel
				);
			}

			if (catched_collision_down)
			{
				EGraphicCore::batch->draw_rama
				(
					*selected_entity->position_x - *selected_entity->collision_left - 3.0f,
					*selected_entity->position_y - *selected_entity->collision_down - 3.0f,
					*selected_entity->collision_left + *selected_entity->collision_right + 3.0f,
					6.0f,
					1.0f,
					EGraphicCore::gabarite_white_pixel
				);
			}
		}

		if (*entity_gabarite_mode_active == EntityGabariteMode::EntityGabaritePathBlock)
		{
			if (catched_collision_left)
			{
				EGraphicCore::batch->draw_rama
				(
					*selected_entity->position_x - *selected_entity->path_block_gabarite_left - 3.0f,
					*selected_entity->position_y - *selected_entity->path_block_gabarite_down - 3.0f,
					6.0f,
					*selected_entity->path_block_gabarite_down + *selected_entity->path_block_gabarite_up + 3.0f,
					1.0f,
					EGraphicCore::gabarite_white_pixel
				);
			}

			if (catched_collision_up)
			{
				EGraphicCore::batch->draw_rama
				(
					*selected_entity->position_x - *selected_entity->path_block_gabarite_left - 3.0f,
					*selected_entity->position_y + *selected_entity->path_block_gabarite_up - 3.0f,
					*selected_entity->path_block_gabarite_left + *selected_entity->path_block_gabarite_right + 3.0f,
					6.0f,
					1.0f,
					EGraphicCore::gabarite_white_pixel
				);
			}

			if (catched_collision_right)
			{
				EGraphicCore::batch->draw_rama
				(
					*selected_entity->position_x + *selected_entity->path_block_gabarite_right - 3.0f,
					*selected_entity->position_y - *selected_entity->path_block_gabarite_down - 3.0f,
					6.0f,
					*selected_entity->path_block_gabarite_down + *selected_entity->path_block_gabarite_up + 3.0f,
					1.0f,
					EGraphicCore::gabarite_white_pixel
				);
			}

			if (catched_collision_down)
			{
				EGraphicCore::batch->draw_rama
				(
					*selected_entity->position_x - *selected_entity->path_block_gabarite_left - 3.0f,
					*selected_entity->position_y - *selected_entity->path_block_gabarite_down - 3.0f,
					*selected_entity->path_block_gabarite_left + *selected_entity->path_block_gabarite_right + 3.0f,
					6.0f,
					1.0f,
					EGraphicCore::gabarite_white_pixel
				);
			}
		}

		
	}

	//rama selector
	if (rama_start_selection)
	{
		EGraphicCore::batch->setcolor(EColor::COLOR_RED);
		EGraphicCore::batch->draw_rama(rama_selector_start_x, rama_selector_start_y, rama_selector_end_x - rama_selector_start_x, rama_selector_end_y - rama_selector_start_y, 2.0f / EWindow::window_test->game_camera->zoom, EGraphicCore::gabarite_white_pixel);
	}

	/*
	if
	(
		(glfwGetKey(EWindow::main_window, GLFW_KEY_B) == GLFW_PRESS)
		&
		(!EButton::any_input)
		&
		(editor_mode == EditMode::EditAutobuilding)
	)
	{
		EGraphicCore::batch->setcolor(EColor::COLOR_PINK);
		EGraphicCore::batch->draw_rama
		(
			*selected_entity->position_x
			+
			*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->offset_x
			+
			*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->offset_x
			+
			*selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(autobuilding_selected_wall)->texture_variant_list.at(autobuilding_selected_texture_variant)->offset_x
			, 
			
			
			rama_selector_start_y, rama_selector_end_x - rama_selector_start_x, rama_selector_end_y - rama_selector_start_y, 2.0f / EWindow::window_test->game_camera->zoom, EGraphicCore::gabarite_white_pixel);
	}*/
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
	link_to_add_new_sprite_button->master_button = sprite_button_list.at(selected_sprite_id);
	link_to_is_rotate_by_move_button->master_button = sprite_button_list.at(selected_sprite_id);

	for (EButton* b : link_to_sprite_editor_group)
	{
		{b->is_active = editor_mode == EditMode::EditSprites;}
	}

	EString::out_debug("1");

	//mark button as inactive (invisible)
	for (EButton* b : sprite_button_list)
	{
		b->is_active = false;
	}

	//EString::out_debug("2");

	int id = 0;
	float yy = -10.0f;

	if ((editor_mode == EditMode::EditSprites) & (selected_entity != NULL))
	{

		selected_or_unselected_color(link_to_is_rotate_by_move_button, *selected_entity->sprite_list.at(selected_sprite_id)->rotate_by_move);
		selected_or_unselected_color(link_to_is_rotate_by_gun_target_button, *selected_entity->sprite_list.at(selected_sprite_id)->rotate_by_target_gun);
		selected_or_unselected_color(link_to_is_wall_mode, *selected_entity->sprite_list.at(selected_sprite_id)->wall_mode);
		selected_or_unselected_color(link_to_is_shadow, *selected_entity->sprite_list.at(selected_sprite_id)->is_shadow);

		if (selected_entity != NULL)
		{
			//for all sprite button
			for (int i = 0; i < selected_entity->sprite_list.size(); i++)
			if (i < sprite_button_list.size())
			{
				std::cout << "you are retarded? " << std::to_string(i) << std::endl;

				sprite_button_list.at(i)->button_y = yy;//align button
				std::cout << "sprite_button_list.at(i)->button_y = yy;" << std::endl;

				sprite_button_list.at(i)->is_active = true;//active by default
				std::cout << "sprite_button_list.at(i)->is_active = true;" << std::endl;
				//sprite_button_list.at(i)->gabarite = selected_entity->sprite_list.at(i)->gabarite.at(0);

				yy -= sprite_button_list.at(i)->button_size_y + 10.0f;
				std::cout << "yy -= sprite_button_list.at(i)->button_size_y + 10.0f;" << std::endl;


				//currect button is selected
				if (i == selected_sprite_id)
				{
					sprite_button_list.at(i)->description_text = selected_entity->sprite_list.at(i)->sprite_struct_list.at(0)->gabarite->name;//set_description

					//check selected frame bound
					if (selected_frame_id >= selected_entity->sprite_list.at(i)->sprite_struct_list.size())
					{selected_frame_id = selected_entity->sprite_list.at(i)->sprite_struct_list.size() - 1;}

					//set color of selected button
					sprite_button_list.at(i)->rama_color->set_color(EColor::COLOR_ORANGE);
					sprite_button_list.at(i)->rama_thikness = 5.0f;


					yy -= 80.0f;
					
					//set texture as selected frame
					sprite_button_list.at(i)->gabarite = selected_entity->sprite_list.at(i)->sprite_struct_list.at(selected_frame_id)->gabarite;
				}
				else
				{
					//color as unselected
					sprite_button_list.at(i)->rama_color->set_color(EColor::COLOR_BLACK);
					sprite_button_list.at(i)->rama_thikness = 2.0f;

					//std::cout << "vector size:" << sprite_button_list.size() << " id:" << i << std::endl;

					/*sprite_button_list.at(i)->gabarite
					=
					selected_entity->sprite_list.at(i)
					->gabarite.at(selected_frame_id);*/
					sprite_button_list.at(i)->gabarite = selected_entity->sprite_list.at(i)->sprite_struct_list.at(0)->gabarite;
				}

				sprite_button_list.at(i)->data_id = i;
			}

			
			//id order frame
			for (EButton* b : link_to_sprite_frame)
			{
				b->master_button = sprite_button_list.at(selected_sprite_id);
			}

			int frame_data_id = 0;
			for (int zzz = 0; zzz < link_to_sprite_frame.size(); zzz++)
			{
			
				EButton* fr = link_to_sprite_frame.at(zzz);
				//std::cout << "process:" << z << std::endl;

				
				if (zzz < selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.size())
				{
					fr->is_active = true;

					fr->gabarite = selected_entity->sprite_list.at(selected_sprite_id)->sprite_struct_list.at(frame_data_id)->gabarite;

					fr->data_id = frame_data_id;

					frame_data_id++;
				}
				else
				{
					fr->is_active = false;
				}






				if (zzz == selected_frame_id)
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

		/*
		link_to_add_new_sprite_button->button_x = sprite_button_list.at(selected_sprite_id)->button_x + link_to_add_new_sprite_button->button_size_x + 10.0f;
		link_to_add_new_sprite_button->button_y = sprite_button_list.at(selected_sprite_id)->button_y - 20.0f;*/
	}
	
}

void EWindowEditor::reset_mode(ESprite* _spr)
{
	*_spr->rotate_by_move = false;
	*_spr->rotate_by_target = false;
	*_spr->wall_mode = false;
	*_spr->rotate_by_target_gun = false;
}

void EWindowEditor::update_on_entity_select()
{
	if (selected_entity != NULL)
	{
		for (EButton* b : float_data_button_list)
		{
			b->text = EString::float_to_string(selected_entity->eattr_BASE.at(b->data_id));
		}

		for (EButton* b : bool_data_button_list)
		{
			//b->text = std::to_string(selected_entity->eattr_BASE.at(b->data_id));

			selected_or_unselected_color(b, *selected_entity->pointer_to_bool_list.at(b->data_id));
		}

		link_to_lightsource_red->slider_value = *selected_entity->light_source_red;
		link_to_lightsource_green->slider_value = *selected_entity->light_source_green;
		link_to_lightsource_blue->slider_value = *selected_entity->light_source_blue;
	}
}

void EWindowEditor::add_button_group_for_float_data(int _data_id)
{


	int id = -1;

	for (int i = 0; i < Entity::entity_attribute_names.size(); i++)
	{
		if (Entity::entity_attribute_id.at(i) == _data_id) { id = i; break; }
	}


	if (id != -1)
	{
		EButton* b = new EButton(button_group_start_x, button_group_start_y, 50.0f, 20.0f);
		b->master_position = Enums::PositionMaster::WINDOW;
		b->master_window = this;
		b->have_input_mode = true;

		b->is_active = true;

		b->position_mode_x = Enums::PositionMode::RIGHT;
		b->position_mode_y = Enums::PositionMode::DOWN;

		b->input_only_numbers = true;

		*b->side_text = Entity::entity_attribute_names.at(id);
		b->data_id = id;

		b->action_on_input_finish = &EBA::action_set_entity_float_attribute;

		float_data_button_list.push_back(b);
		button_list.push_back(b);

		button_group_start_y -= 25.0f;
	}
}

void EWindowEditor::add_button_group_for_bool_data(int _data_id)
{
	int id = -1;

	for (int i = 0; i < Entity::entity_bool_attribute_names.size(); i++)
	{
		if (Entity::entity_bool_attribute_id.at(i) == _data_id) { id = i; break; }
	}


	if (id != -1)
	{
		EButton* b = new EButton(button_group_start_x, button_group_start_y, 240.0f, 20.0f);
		b->master_position = Enums::PositionMaster::WINDOW;
		b->master_window = this;

		b->is_active = true;

		b->position_mode_x = Enums::PositionMode::RIGHT;
		b->position_mode_y = Enums::PositionMode::DOWN;

		b->text = Entity::entity_bool_attribute_names.at(id);
		b->data_id = id;

		b->action_on_left_click = &EBA::action_set_entity_bool_attribute;

		bool_data_button_list.push_back(b);
		button_list.push_back(b);

		button_group_start_y -= 25.0f;
	}
}

void EWindowEditor::refresh_autobuilding()
{
	editor_mode = EditMode::EditAutobuilding;
	//Entity::assembly_autobuilding_sprites(EWindow::window_editor->selected_entity);
	Entity::update_building_autogenerator_massive(EWindow::window_editor->selected_entity);

	select_new_floor();
	select_new_wall();
	select_new_variant();
}

void EWindowEditor::select_new_variant()
{
	if (count_of_variants > 0)
	{
		for (EButton* b : link_to_texture_variant_array->button_list)
		{
			if (b->data_id == autobuilding_selected_texture_variant)
			{

				b->bg_color->set_color(EColor::COLOR_WHITE);
				b->rama_thikness = 3.0f;
				b->rama_color->set_color(EColor::COLOR_YELLOW);

				EWindow::window_editor->building_autogenerator_wall_button_link.at(autobuilding_selected_wall)->gabarite
					=
					b->gabarite;
			}
			else
			{
				b->bg_color->set_color_alpha(EColor::COLOR_BLACK, 0.5f);
				b->rama_thikness = 1.0f;
				b->rama_color->set_color(EColor::COLOR_BLACK);
			}
		}

		EWindow::window_editor->editor_mode = EWindowEditor::EditMode::EditAutobuilding;
	}
}

void EWindowEditor::select_new_floor()
{
	if (count_of_floors > 0)
	{
		if (autobuilding_selected_floor >= count_of_floors)
		{
			autobuilding_selected_floor = count_of_floors - 1;
		}

		int id = 0;
		for (EButton* b : link_to_floors_array->button_list)
		{
			if (b->data_id == autobuilding_selected_floor)
			{

				b->bg_color->set_color(EColor::COLOR_WHITE);
				b->rama_thikness = 3.0f;
				b->rama_color->set_color(EColor::COLOR_YELLOW);
			}
			else
			{
				b->bg_color->set_color_alpha(EColor::COLOR_GRAY, 0.75f);
				b->rama_thikness = 1.0f;
				b->rama_color->set_color(EColor::COLOR_BLACK);
			}

			/**if (id < selected_entity->autobuilding_floor_list.size())
			{b->is_active = true;}
			else
			{b->is_active = false;}

			id++;*/
		}


		for (int i = 0; i < EWindow::window_editor->building_autogenerator_wall_button_link.size(); i++)
			if
				(
					(EWindow::window_editor->selected_entity->autobuilding_floor_list.size() > 0)
					&&
					(EWindow::window_editor->selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(i)->texture_variant_list.size() > 0)
				)
			{
				building_autogenerator_wall_button_link.at(i)->gabarite
					=
					EWindow::window_editor->selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->wall_list.at(i)->texture_variant_list.at(0)->texture;
			}
			else
			{
				building_autogenerator_wall_button_link.at(i)->gabarite = NULL;
			}

			link_to_horizontal_floor_slider->slider_value = *selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->horizontal_roof_offset_multiplier;
			link_to_horizontal_floor_slider->target_address_for_float = selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->horizontal_roof_offset_multiplier;

			link_to_bottom_floor_slider->slider_value = *selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->bottom_roof_offset_multiplier;
			link_to_bottom_floor_slider->target_address_for_float = selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->bottom_roof_offset_multiplier;

			link_to_up_floor_slider->slider_value = *selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->up_roof_offset_multiplier;
			link_to_up_floor_slider->target_address_for_float = selected_entity->autobuilding_floor_list.at(autobuilding_selected_floor)->up_roof_offset_multiplier;

		}
}

void EWindowEditor::select_new_wall()
{
	for (int i = 0; i < EWindow::window_editor->building_autogenerator_wall_button_link.size(); i++)
	{
		EButton* sbut = EWindow::window_editor->building_autogenerator_wall_button_link.at(i);


		//selected
		if
			(
				(selected_entity->autobuilding_floor_list.size() > 0)
				&&
				(
					selected_entity->
					autobuilding_floor_list.at(autobuilding_selected_floor)->
					wall_list.at(i)->
					texture_variant_list.size() > 0
				)
			)
		{
			if (i == EWindow::window_editor->autobuilding_selected_wall)
			{
				sbut->rama_thikness = 3.0f;

				sbut->rama_color->set_color(EColor::COLOR_YELLOW);
				sbut->bg_color->set_color(EColor::COLOR_WHITE);
			}
			else
			{


				sbut->rama_thikness = 1.0f;

				sbut->rama_color->set_color(EColor::COLOR_BLACK);
				sbut->bg_color->set_color(EColor::COLOR_GRAY);


			}
		}
		else
		{
				sbut->rama_thikness = 1.0f;

				sbut->rama_color->set_color(EColor::COLOR_GRAY);
				sbut->bg_color->set_color(EColor::COLOR_BLACK);
		}
	}


}
