#include "NSW_api/EWindow.h"
#include "ECamera.h"
#include "EntityManager.h"

class EWindowEditor : public EWindow
{
public:
	EWindowEditor();
	~EWindowEditor();

	enum EditMode {SelectEntities, EditSprites};

	int editor_mode = 0;

	std::vector <EButton*> sprite_button_list;
	Entity* selected_entity;
	int selected_sprite_id;
	int selected_frame_id;
	EButton* selected_sprite_button;

	bool started_sprite_move;
	bool started_entity_move;
	bool started_collision_move;

	EButton* link_to_add_new_sprite_button;
	EButton* link_to_move_sprite_up;
	EButton* link_to_move_sprite_down;

	std::vector<EButton*> link_to_sprite_frame;
	std::vector<EButton*> link_to_sprite_editor_group;

	virtual void update(float _d);
	virtual void draw(float _d);
	virtual void draw_interface(float _d);

	bool catched_collision_up = false;
	bool catched_collision_down = false;
	bool catched_collision_left = false;
	bool catched_collision_right = false;


	void update_sprite_buttons();

	float sprite_flash_cooldown = 0.5;


};