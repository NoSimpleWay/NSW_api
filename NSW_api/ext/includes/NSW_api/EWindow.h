#pragma once



#include <glad/glad.h>
#include <GLFW/glfw3.h>
//glm::mat4 matrix_transform;

#include "NSW_api/Batcher.h"
#include <vector>
#include "NSW_api/EFont.h"



#include <iostream>
#include <chrono>

#include "NSW_api/ETextureAtlas.h"
#include "NSW_api/EButton.h"

#include "NSW_api/EUtils.h"

//#include "NSW_api/EWindowTest.h"

class EButton;
class EWindowTest;
class EWindowEditor;
class EWindowSearchBrick;

class EWindow
{
public:
	void default_update(float _d);
	virtual void update(float _d);

	void default_draw(float _d);
	virtual void draw(float _d);

	void default_resize_event();


	virtual void draw_interface(float _d);
	void default_draw_interface(float _d);

	void static add_time_process(std::string _name);

	static GLFWwindow* main_window;

	static unsigned int transformLoc;

	float offset_x = 0;
	float offset_y = 0;

	float position_x = 0;
	float position_y = 0;
	
	float window_size_x = 100.0f;
	float window_size_y = 100.0f;

	static double mouse_x;
	static double mouse_y;
	
	static int prev_mouse_x;
	static int prev_mouse_y;

	static int saved_pos_x;
	static int saved_pos_y;

	static float mouse_speed_x;
	static float mouse_speed_y;

	static float real_mouse_x;
	static float real_mouse_y;

	static bool LMB;
	static bool RMB;

	static bool system_button_release;

	static double scroll;

	//static std::pair<float, std::string> time_process;

	struct time_process_struct
	{
		std::vector<float> time_process_value;
		std::string time_process_name;
	};

	static std::vector<time_process_struct*> tps_list;

	static int time_process_rota_id;
	static std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;

	static void push_cursor(float _x, float _y);

	EWindow();
	~EWindow();

	static Batcher* batch;
	static std::vector<EWindow*> window_list;
	static float delete_button_hold_time;

	static EWindowTest* window_test;
	static EWindowEditor* window_editor;
	static EWindowSearchBrick* window_search_brick;

	static ETextureAtlas* default_texture_atlas;
	static ETextureAtlas* shadow_FBO;
	static ETextureAtlas* shadow_ground_FBO;
	static ETextureAtlas* lightmap_FBO;
	static ETextureAtlas* lightmap_FBO2;
	static ETextureAtlas* base_lightmap;

	static bool button_pressed;

	static bool button_main_group_pressed;

	static bool button_right_pressed;
	static bool button_backspace_released;
	bool is_active = true;
	int id = 0;

	static bool is_overlap(EWindow* _w);

	static char last_inputed_char;

	std::vector <EButton*> button_list;
	std::vector <EButton*> default_button_list;

	bool always_fullscreen;
	bool have_bg = false;

	int align_x;
	int align_y;


	//void draw_lightmap();

};