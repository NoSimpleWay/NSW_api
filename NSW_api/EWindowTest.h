#include "NSW_api/EWindow.h"
#include "ECamera.h"
#include "EntityManager.h"
#include "EPath.h"

class EWindowTest : public EWindow
{
public:
	EWindowTest();
	~EWindowTest();

	bool time_process_active = true;

	void default_update(float _d);
	virtual void update(float _d);

	void default_draw(float _d);
	void draw_shadows();
	virtual void draw(float _d);

	virtual void draw_interface(float _d);

	//
		int draw_border_left;
		int draw_border_right;

		int draw_border_down;
		int draw_border_up;
	//



	//
		int update_border_left;
		int update_border_right;

		int update_border_down;
		int update_border_up;
	//

		int left_path_draw;
		int right_path_draw;

		int down_path_draw;
		int up_path_draw;

		float free_camera_x;
		float free_camera_y;

	Entity* link_to_player;

	ECamera* game_camera = new ECamera();

	std::vector<Entity*> new_added_entity_list;

	std::vector <EGabarite*> terrain_textures_list;

	short terrain[EPath::PATH_DIM][EPath::PATH_DIM];
	
	void generate_terrain();

	float crosshair_pos_x;
	float crosshair_pos_y;

	float crosshair_add_x;
	float crosshair_add_y;

};