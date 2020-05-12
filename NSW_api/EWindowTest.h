#include "NSW_api/EWindow.h"
#include "ECamera.h"
#include "EntityManager.h"

class EWindowTest : public EWindow
{
public:
	EWindowTest();
	~EWindowTest();

	bool time_process_active = true;

	void default_update(float _d);
	virtual void update(float _d);

	void default_draw(float _d);
	virtual void draw(float _d);

	virtual void draw_interface(float _d);

		int draw_border_left;
		int draw_border_right;

		int draw_border_down;
		int draw_border_up;

		int left_path_draw;
		int right_path_draw;

		int down_path_draw;
		int up_path_draw;

		float free_camera_x;
		float free_camera_y;

	Entity* link_to_player;

	ECamera* game_camera = new ECamera();

	std::vector<Entity*> new_added_entity_list;

};