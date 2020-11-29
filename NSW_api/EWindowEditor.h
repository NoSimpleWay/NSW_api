#include "NSW_api/EWindow.h"
#include "ECamera.h"
#include "EntityManager.h"
#include "EBA.h"

class EWindowEditor : public EWindow
{
public:
	EWindowEditor();
	~EWindowEditor();

	enum EditMode {SelectEntities, EditSprites, EditAutobuilding};
	enum MoveMode {MoveTexture, MoveWall, MoveFloor};
	enum EntityGabariteMode {EntityGabariteCollision, EntityGabaritePathBlock, EntityGabariteShadowBlock};

	int* entity_gabarite_mode_active = new int(EntityGabariteMode::EntityGabariteCollision);
	int editor_mode = 0;
	int move_mode = 0;

	std::vector <EButton*> sprite_button_list;
	Entity* selected_entity;
	Entity* prev_entity;
	int selected_sprite_id;
	int selected_frame_id;
	EButton* selected_sprite_button;

	std::vector <Entity*> selected_entity_list;

	bool started_sprite_move;
	bool started_shadow_resize;
	bool started_shadow_tall;
	bool started_shadow_bottom_tall;
	bool started_entity_move;
	bool started_z_move;
	bool started_collision_move;

	EButton* link_to_add_new_sprite_button;
	EButton* link_to_move_sprite_up;
	EButton* link_to_move_sprite_down;

	EButton* link_to_is_rotate_by_move_button;
	EButton* link_to_is_rotate_by_gun_target_button;
	EButton* link_to_is_wall_mode;
	EButton* link_to_is_shadow;

	EButton* link_to_shadow_color_red;
	EButton* link_to_shadow_color_green;
	EButton* link_to_shadow_color_blue;

	EButton* link_to_sky_color_red;
	EButton* link_to_sky_color_green;
	EButton* link_to_sky_color_blue;

	EButton* link_to_lightsource_red;
	EButton* link_to_lightsource_green;
	EButton* link_to_lightsource_blue;

	std::vector<EButton*> link_to_sprite_frame;
	std::vector<EButton*> link_to_sprite_editor_group;

	static float get_move_multiplier(float _zoom);

	virtual void update(float _d);
	void clone_entity(Entity* _e);
	virtual void draw(float _d);
	virtual void draw_interface(float _d);

	void selected_or_unselected_color(EButton* _b, bool _selected);

	bool catched_collision_up = false;
	bool catched_collision_down = false;
	bool catched_collision_left = false;
	bool catched_collision_right = false;


	void update_sprite_buttons();
	void reset_mode(ESprite* _spr);

	float sprite_flash_cooldown = 0.5;

	bool rama_start_selection = false;
	float rama_selector_start_x;
	float rama_selector_start_y;
	float rama_selector_end_x;
	float rama_selector_end_y;

	EButton* link_to_entity_mass_button;
	EButton* link_to_entity_inmovable_button;
	EButton* link_to_entity_shadow_tall_button;
	EButton* link_to_entity_propeties_button;
	EButton* link_to_entity_controlled_by_player_button;
	EButton* link_to_entity_controlled_by_AI_button;
	EButton* link_to_set_camera_target_button;


	void update_on_entity_select();

	float button_group_start_x;
	float button_group_start_y;

	void add_button_group_for_float_data(int _data_id);
	void add_button_group_for_bool_data(int _data_id);

	std::vector <EButton*> float_data_button_list;
	std::vector <EButton*> bool_data_button_list;

	std::vector <EButton*> select_gabarite_mode_button_list;






	/*
	
	SECTION OF LINKS TO BUILDING AUTOGNERATOR
	
	*/


	//left wall as selected
	/*
	EButton* building_autogenerator_link_to_left_wall;
	EButton* building_autogenerator_link_to_right_wall;
	EButton* building_autogenerator_link_to_mid_wall;
	EButton* building_autogenerator_link_to_window_wall;*/

	//left wall / mid wall / right wall / window
	int autobuilding_selected_wall;
	std::vector<EButton*> building_autogenerator_wall_button_link;
	
	//texture variants of selected wall
	int autobuilding_selected_texture_variant;
	std::vector <EButton*> building_autogenerator_link_to_texture_variant;

	//int autobuilding_selected_floor;
	//selected floor
	int autobuilding_selected_floor;
	std::vector<EButton*> floor_button;

	EButton* texture_variant_style_button;

	button_array_collection_massive* autobuilding_massive_link;

	button_array* link_to_texture_variant_array;
	button_array* link_to_floors_array;

	EButton* link_to_bottom_floor_slider;
	EButton* link_to_up_floor_slider;
	EButton* link_to_horizontal_floor_slider;

	void refresh_autobuilding();

	void select_new_variant();
	void select_new_floor();
	void select_new_wall();

	int count_of_variants;
	int count_of_floors;

	static EButton* link_to_blur_button;
	static EButton* link_to_blend_button;
	static EButton* link_to_decay_button;

	static EButton* link_to_bottom_tall_button;
	static EButton* link_to_upper_tall_button;







};