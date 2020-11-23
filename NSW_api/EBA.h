#pragma once
#include "EntityManager.h"
#include "NSW_api/EWindow.h"

class EBA
{
public:
	EBA();
	~EBA();


	static void set_method(void (*function)());

	static void do_something();

	static void action_add_new_sprite(EButton* _b, float _d);
	static void action_select_sprite(EButton* _b, float _d);
	static void action_set_sprite_texture(EButton* _b, float _d);
	static void action_open_select_texture_window(EButton* _b, float _d);

	static void action_set_button_as_removed(EButton* _b, float _d);
	static void action_close_window(EButton* _b, float _d);

	static void action_save_map(EButton* _b, float _d);
	static void action_save_entity_to_collection(EButton* _b, float _d);
	static void save_to_file(std::string& w_string, Entity* e, int& order, bool _to_collection);
	static void read_data_for_entity(std::ifstream& myfile);
	static void action_load_map(EButton* _b, float _d);
	static void action_load_entity_collection(EButton* _b, float _d);

	static void action_add_new_entity_from_collection(EButton* _b, float _d);
	static void action_add_new_entity(EButton* _b, float _d);
	static void action_open_select_entity_collection_window(EButton* _b, float _d);

	static void action_select_frame(EButton* _b, float _d);

	static void action_move_sprite_up(EButton* _b, float _d);
	static void action_move_sprite_down(EButton* _b, float _d);

	static void action_set_sprite_mode_4(EButton* _b, float _d);
	static void action_set_sprite_mode_8(EButton* _b, float _d);

	static void action_slider_shadow_color(EButton* _b, float _d);
	static void action_slider_light_source_color(EButton* _b, float _d);
	static void action_slider_sky_color(EButton* _b, float _d);

	static void action_select_entity_gabarite_mode(EButton* _b, float _d);

	//static void action_slider_sky_color(EButton* _b, float _d);





	//actions_for_input
	static void action_input_search_brick(EButton* _b, float _d);
	static void action_set_sprite_mode_wall(EButton* _b, float _d);
	static void action_set_shadow_mode(EButton* _b, float _d);

	static void action_set_mass(EButton* _b, float _d);
	static void action_set_tall(EButton* _b, float _d);

	static void action_set_inmovable(EButton* _b, float _d);
	static void action_set_controlled_by_player(EButton* _b, float _d);
	static void action_set_controlled_by_AI(EButton* _b, float _d);
	static void action_set_camera_target(EButton* _b, float _d);

	static void action_set_light_power(EButton* _b, float _d);
	static void action_set_value_by_data_id(EButton* _b, float _d);
	static void action_set_entity_float_attribute(EButton* _b, float _d);
	static void action_set_entity_bool_attribute(EButton* _b, float _d);


	static void action_set_constant_int_to_address(EButton* _b, float _d);
	static void action_set_constant_bool_to_address(EButton* _b, float _d);

	static void action_set_button_value_float_to_address(EButton* _b, float _d);

	static void action_add_new_texture_variant_button(EButton* _b, float _d);
	

	static void action_deactivate_texture_variant(EButton* _b, float _d);
	static void action_deactivate_floors(EButton* _b, float _d);
	static void action_add_new_floor(EButton* _b, float _d);
	static void action_move_floor_order(EButton* _b, float _d);

	static void action_select_building_autogenerator_wall_element(EButton* _b, float _d);
	static void action_select_floor(EButton* _b, float _d);
	static void action_select_texture_variant(EButton* _b, float _d);

	static void action_assembly_autobuilding(EButton* _b, float _d);





	//hit action


	
};