#include "NSW_api/EWindow.h"
#include "ECamera.h"
#include "EntityManager.h"
#include "EBA.h"

class EWindowEditor : public EWindow
{
public:
	EWindowEditor();
	~EWindowEditor();

	enum EditMode {SelectEntities, EditSprites};

	int editor_mode = 0;

	std::vector <EButton*> sprite_button_list;
	Entity* selected_entity;
	Entity* prev_entity;
	int selected_sprite_id;
	int selected_frame_id;
	EButton* selected_sprite_button;

	std::vector <Entity*> selected_entity_list;

	bool started_sprite_move;
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


};