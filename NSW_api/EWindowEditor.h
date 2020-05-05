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

	EButton* link_to_add_new_sprite_button;

	virtual void update(float _d);
	virtual void draw(float _d);
	virtual void draw_interface(float _d);

	void update_sprite_buttons();


};