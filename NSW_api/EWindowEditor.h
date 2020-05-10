#include "NSW_api/EWindow.h"
#include "ECamera.h"
#include "EntityManager.h"

class EWindowEditor : public EWindow
{
public:
	EWindowEditor();
	~EWindowEditor();

	std::vector <EButton*> sprite_button_list;
	Entity* selected_entity;
	int selected_sprite_id;
	EButton* selected_sprite_button;

	bool started_sprite_move;
	bool started_entity_move;

	EButton* link_to_add_new_sprite_button;
	EButton* link_to_move_sprite_up;
	EButton* link_to_move_sprite_down;

	virtual void update(float _d);
	virtual void draw(float _d);
	virtual void draw_interface(float _d);

	void update_sprite_buttons();


};