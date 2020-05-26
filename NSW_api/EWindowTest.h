#include "NSW_api/EWindow.h"
#include "ECamera.h"
#include "EntityManager.h"
#include "EPath.h"

class EWindowTest : public EWindow
{
public:
	void test_of_values();
	EWindowTest();
	~EWindowTest();

	bool time_process_active = true;

	void default_update(float _d);
	virtual void update(float _d);

	void default_draw(float _d);
	void draw_shadows();
	void draw_debug_draw_path();
	void draw_debug_collision();
	void draw_debug_entity_position();
	void draw_debug_cluster_border();
	void draw_debug_cluster_rama();
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

		//
		float free_camera_x;
		float free_camera_y;
		
		//
		int left_terrain_draw;
		int right_terrain_draw;

		int down_terrain_draw;
		int up_terrain_draw;

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

	float test_value_A = 17.0f;
	float test_value_B = 6167711.4214f;

	std::vector <float> test_vector = {17.0f, 6167711.4214f};

	EGabarite* terrain_200;

};